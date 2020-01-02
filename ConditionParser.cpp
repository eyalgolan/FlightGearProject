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
  if(symblTbl.isInNameMap(firstExp)){
    firstExpValue = symblTbl.getNameMap()[firstExp].second;
    //cout<<firstExp + " value is " + to_string(firstExpValue)<<endl;
  }
  else {
    firstExpValue = stod(firstExp);
  }
  symblTbl.g_updateLock.unlock();
  double secondExpValue;
  symblTbl.g_updateLock.lock();
  if(symblTbl.isInNameMap(secondExp)){
    secondExpValue = symblTbl.getNameMap()[secondExp].second;
  }
  else {
    secondExpValue = stod(secondExp);
  }
  symblTbl.g_updateLock.unlock();
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