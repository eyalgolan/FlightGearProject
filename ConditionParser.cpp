//
// Created by eyal on 16/12/19.
//

#include "ConditionParser.h"
#include "iostream"
#include "SymbolTable.h"

using namespace std;

int ConditionParser::exec(vector<string> params) {
  int i=1;
  string firstExp = params[i];
  string con=params[i+1];
  string secondExp = params[i+2];
  SymbolTable &symblTbl = SymbolTable::getInstance();
  double firstExpValue;
  symblTbl.g_updateLock.lock();
  if(symblTbl.getNameMap().find(firstExp) != symblTbl.getNameMap().end()){
    firstExpValue = symblTbl.getNameMap()[firstExp].second;
  }
  else {
    firstExpValue = stod(firstExp);
  }
  symblTbl.g_updateLock.unlock();
  double secondExpValue;
  symblTbl.g_updateLock.lock();
  if(symblTbl.getNameMap().find(firstExp) != symblTbl.getNameMap().end()){
    secondExpValue = symblTbl.getNameMap()[secondExp].second;
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
    cout<<"didnt find condition"<<endl;
  }
  return this->numParams;
}
bool ConditionParser::getcontidion() {
  return this->condition;
}
ConditionParser::ConditionParser(vector<string> conditionVector) {
  this->exec(conditionVector);
}