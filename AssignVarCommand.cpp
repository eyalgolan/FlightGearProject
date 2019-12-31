//
// Created by eyal on 24/12/19.
//

#include "AssignVarCommand.h"
#include "SymbolTable.h"
#include "iostream"

using namespace std;

int AssignVarCommand::exec(vector<string> params) {

  string name = params[0];
  double value;
  SymbolTable &symblTbl = SymbolTable::getInstance();
  symblTbl.g_updateLock.lock();
  if(symblTbl.isInNameMap(params[2])) {
    value = symblTbl.getNameMap()[name].second;
  }
  else {
    value = stod(params[2]);
  }
  symblTbl.addToVarMap(name, value);
  symblTbl.g_updateLock.unlock();
  return numParams;
}
