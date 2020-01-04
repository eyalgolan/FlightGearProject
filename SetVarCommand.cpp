//
// Created by eyal on 24/12/19.
//

#include "SetVarCommand.h"
#include "SymbolTable.h"
#include "ConnectCommand.h"
#include "ExpressionHandler.h"

/**
 * Function: exec
 *
 * @param params
 * @return how much to advance in the Parser's input vector
 */
int SetVarCommand::exec(vector<string> params) {
  SymbolTable &symblTbl = SymbolTable::getInstance();


  string name = params[0];
  double value;
  Interpreter *in = new Interpreter();
  Expression* exp = nullptr;
  //symblTbl.g_updateLock.lock();
  string toSet = symblTbl.getSetExp();
  //symblTbl.g_updateLock.unlock();
  in->setVariables(toSet);
  exp = in->interpret(params[1]);
  value = exp->calculate();

  //string name = params[0];
  //double value = stod(params[1]);
  //symblTbl.g_updateLock.lock();
  //string sim = symblTbl.getNameMap()[name].first;
  string sim = symblTbl.getNameMapSim(name);
  //symblTbl.g_updateLock.unlock();
  string command = "set " + sim + " " + to_string(value) + "\r\n";
  symblTbl.updateTable(name, "", value, "setVar");
  writeToQueue(command);
  return numParams;
}

/**
 * Function: writeToQueue
 * Writes commands to Symbol table's command queue
 * @param input: a command to push to the command queue
 */
void SetVarCommand::writeToQueue(string input) {
  SymbolTable &symblTbl = SymbolTable::getInstance();
  symblTbl.pushToQueue(input);
}