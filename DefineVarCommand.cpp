//
// Created by eyal on 16/12/19.
//

#include "DefineVarCommand.h"
#include "SymbolTable.h"
#include "iostream"

using namespace std;

/**
 * Function: exec
 * Add a new var (with name and sim) to the name & sim maps of the symbol table
 * @param params: a vector containing the name and simPath of a new var
 * @return how much to advance in the Parser's input vector
 */
int DefineVarCommand::exec(vector<string> params) {
  SymbolTable &symblTbl = SymbolTable::getInstance();

  string name = params[0];
  string simPath = params[1];
  symblTbl.updateTable(name, simPath, 0, "defineVar");
  return this->numParams;
}
