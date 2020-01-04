//
// Created by eyal on 16/12/19.
//

#include "ConditionParser.h"
#include "iostream"
#include "SymbolTable.h"

using namespace std;

/**
 * Function: exec
 * checks if the condition is satisfied and updates this->condition accordingly
 * @param params the condition's arguments
 * @return how much to advance in the Parser's input vector
 */
int ConditionParser::exec(vector<string> params) {

  //receive params
  string firstExp = params[0];
  string con=params[1];
  string secondExp = params[2];

  //check if the first expression is in the name map or var map
  SymbolTable &symblTbl = SymbolTable::getInstance();
  double firstExpValue;
  symblTbl.g_updateLock.lock();
  bool isFirstExpInNameMap = symblTbl.isInNameMap(firstExp);
  bool isFirstExpInVarMap = symblTbl.isInVarMap(firstExp);
  symblTbl.g_updateLock.unlock();

  if(isFirstExpInNameMap){
    //if it's in the name map, get its value from the name map
    symblTbl.g_updateLock.lock();
    firstExpValue = symblTbl.getNameMapValue(firstExp);
    symblTbl.g_updateLock.unlock();
  }
  else if(isFirstExpInVarMap) {
    //otherwise if its in the var map, get its value from the var map
    symblTbl.g_updateLock.lock();
    firstExpValue = symblTbl.getVarMapValue(firstExp);
    symblTbl.g_updateLock.unlock();
  }
  else {
    //otherwise it's a number
    firstExpValue = stod(firstExp);
  }

  //check if the second expression is in the name map or var map
  double secondExpValue;
  symblTbl.g_updateLock.lock();
  bool isSecondExpInNameMap = symblTbl.isInNameMap(secondExp);
  bool isSecondExpInVarMap = symblTbl.isInVarMap(secondExp);
  symblTbl.g_updateLock.unlock();
  if(isSecondExpInNameMap){
    //if it's in the name map, get its value from the name map
    symblTbl.g_updateLock.lock();
    secondExpValue = symblTbl.getNameMapValue(secondExp);
    symblTbl.g_updateLock.unlock();
  }
  else if(isSecondExpInVarMap) {
    //otherwise if its in the var map, get its value from the var map
    symblTbl.g_updateLock.lock();
    secondExpValue = symblTbl.getVarMapValue(secondExp);
    symblTbl.g_updateLock.unlock();
  }
  else {
    //otherwise it's a number
    secondExpValue = stod(secondExp);
  }

  /*
   * check if the condition is met and set the condition accordingly
   */
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
  return this->numParams;
}