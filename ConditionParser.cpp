//
// Created by eyal on 16/12/19.
//

#include "ConditionParser.h"
#include "iostream"
#include "SymbolTable.h"
#include "ExpressionHandler.h"

using namespace std;

/**
 * Function: exec
 * checks if the condition is satisfied and updates this->condition accordingly
 * @param params the condition's arguments
 * @return how much to advance in the Parser's input vector
 */
int ConditionParser::exec(vector<string> params) {

  //receive params
  string firstStr = params[0];
  string con = params[1];
  string secondStr = params[2];


  /*
  * interprets the condition's expressions
  */
  Interpreter *inCondition = new Interpreter();
  Expression *firstExp = nullptr;
  Expression *secondExp = nullptr;
  double firstExpValue;
  double secondExpValue;
  SymbolTable &symblTbl = SymbolTable::getInstance();
  symblTbl.g_updateLock.lock();
  string toSet = symblTbl.getSetExp();
  symblTbl.g_updateLock.unlock();
  inCondition->setVariables(toSet);
  firstExp = inCondition->interpret(firstStr);
  firstExpValue = firstExp->calculate();
  secondExp = inCondition->interpret(secondStr);
  secondExpValue = secondExp->calculate();

  /*
   * check if the condition is met and set the condition accordingly
   */
  if (con == ">") {
    if (firstExpValue > secondExpValue) {
      this->condition = true;
    } else {
      this->condition = false;
    }
  } else if (con == ">=") {
    if (firstExpValue >= secondExpValue) {
      this->condition = true;
    } else {
      this->condition = false;
    }
  } else if (con == "<") {
    if (firstExpValue < secondExpValue) {
      this->condition = true;
    } else {
      this->condition = false;
    }
  } else if (con == "<=") {
    if (firstExpValue <= secondExpValue) {
      this->condition = true;
    } else {
      this->condition = false;
    }
  } else if (con == "==") {
    if (firstExpValue == secondExpValue) {
      this->condition = true;
    } else {
      this->condition = false;
    }
  } else if (con == "!=") {
    if (firstExpValue != secondExpValue) {
      this->condition = true;
    } else {
      this->condition = false;
    }
  }
  return this->numParams;
}