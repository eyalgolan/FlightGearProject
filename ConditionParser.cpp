//
// Created by eyal on 16/12/19.
//

#include "ConditionParser.h"
#include "iostream"
#include "SymbolTable.h"

using namespace std;

int ConditionParser::exec(vector<string> params) {
  int i=0;
  string firstExp = params[i];
  string con=params[i+1];
  string secondExp = params[i+2];
  //cout<<"firstExp: " + firstExp + " , secondExp: " + secondExp<<endl;
  SymbolTable &symblTbl = SymbolTable::getInstance();
  double firstExpValue;
  symblTbl.g_updateLock.lock();
  bool isFirstExpInNameMap = symblTbl.isInNameMap(firstExp);
  symblTbl.g_updateLock.unlock();
  if(isFirstExpInNameMap){
    symblTbl.g_updateLock.lock();
    firstExpValue = symblTbl.getNameMapValue(firstExp);
    symblTbl.g_updateLock.unlock();
    //firstExpValue = symblTbl.getNameMap()[firstExp].second;
    //cout<<firstExp + " value is " + to_string(firstExpValue)<<endl;
  }
  else {
    firstExpValue = stod(firstExp);
  }
  double secondExpValue;
  symblTbl.g_updateLock.lock();
  bool isSecondExpInNameMap = symblTbl.isInNameMap(secondExp);
  symblTbl.g_updateLock.unlock();
  if(isSecondExpInNameMap){
    symblTbl.g_updateLock.lock();
    secondExpValue = symblTbl.getNameMapValue(secondExp);
    symblTbl.g_updateLock.unlock();
    //secondExpValue = symblTbl.getNameMap()[secondExp].second;
  }
  else {
    secondExpValue = stod(secondExp);
  }
  if(con == ">"){
    if(firstExpValue > secondExpValue) {
      this->condition = true;
    }
    else{
      this->condition = false;
    }
  }
  else if(con == ">="){
    if(firstExpValue >= secondExpValue) {
      this->condition = true;
    }
    else{
      this->condition = false;
    }
  }
  else if(con == "<"){
    if(firstExpValue < secondExpValue) {
      this->condition = true;
    }
    else {
      this->condition = false;
    }
  }
  else if(con == "<="){
    if(firstExpValue <= secondExpValue) {
      this->condition = true;
    }
    else {
      this->condition = false;
    }
  }
  else if(con == "=="){
    if(firstExpValue == secondExpValue) {
      this->condition = true;
    }
    else{
      this->condition = false;
    }
  }
  else if(con == "!="){
    if(firstExpValue != secondExpValue) {
      this->condition = true;
    }
    else {
      this->condition = false;
    }
  }
  else{
    //cout<<"didnt find condition"<<endl;
  }
  return this->numParams;
}
bool ConditionParser::getcontidion() {
  return this->condition;
}
//ConditionParser::ConditionParser(vector<string> conditionVector) {
//  this->exec(conditionVector);
//}