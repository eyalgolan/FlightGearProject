//
// Created by eyal on 24/12/19.
//

#include "AssignVarCommand.h"
#include "SymbolTable.h"
#include "iostream"
#include "ExpressionHandler.h"
#include "Expression.h"
using namespace std;
/**
 * AssignVarCommand
 * in this func we use the interpreter to evaluate given expression
 * and add it to our var map.
 * @param params
 * @return  how much to advance in the input vector
 */
int AssignVarCommand::exec(vector<string> params) {

  string name = params[0];
  SymbolTable &symblTbl = SymbolTable::getInstance();
  double value;
  Interpreter *in = new Interpreter();
  Expression *exp = nullptr;
  symblTbl.g_updateLock.lock();
  string toSet = symblTbl.getSetExp();
  symblTbl.g_updateLock.unlock();
  in->setVariables(toSet);
  exp = in->interpret(params[2]);
  value = exp->calculate();
  symblTbl.g_updateLock.lock();
  symblTbl.addToVarMap(name, value);
  symblTbl.g_updateLock.unlock();
  return numParams;
}
