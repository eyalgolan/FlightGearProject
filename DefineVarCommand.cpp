//
// Created by eyal on 16/12/19.
//

#include "DefineVarCommand.h"
#include "SymbolTable.h"
#include "iostream"

using namespace std;

/**
 *
 * @param params
 * @return
 */
int DefineVarCommand::exec(vector<string> params) {
  SymbolTable &symblTbl = SymbolTable::getInstance();

  string name = params[0];
  string simPath = params[1];
  symblTbl.updateTable(name, simPath, 0, "defineVar");
  return this->numParams;
}
