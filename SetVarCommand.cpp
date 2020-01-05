//
// Created by eyal on 24/12/19.
//

#include "SetVarCommand.h"
#include "SymbolTable.h"
#include "ConnectCommand.h"
#include "ExpressionHandler.h"

/**
 * Function: exec
 * sets a new value to a var, updates the symbol table and simulator
 * @param params: a vector containing the var name and new value
 * @return how much to advance in the Parser's input vector
 */
int SetVarCommand::exec(vector<string> params) {
  SymbolTable &symblTbl = SymbolTable::getInstance();

  //interprets the input parameter
  string name = params[0];
  double value;
  Interpreter *in = new Interpreter();
  Expression *exp = nullptr;
  symblTbl.g_updateLock.lock();
  string toSet = symblTbl.getSetExp();
  symblTbl.g_updateLock.unlock();
  in->setVariables(toSet);
  exp = in->interpret(params[1]);
  value = exp->calculate();

  /*
   * builds the command, updates the symbol table and write the command to the
   * command queue
   */
  symblTbl.g_updateLock.lock();
  string sim = symblTbl.getNameMapSim(name);
  symblTbl.g_updateLock.unlock();
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
  symblTbl.g_updateLock.lock();
  symblTbl.pushToQueue(input);
  symblTbl.g_updateLock.unlock();
}