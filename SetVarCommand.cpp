//
// Created by eyal on 24/12/19.
//

#include "SetVarCommand.h"
#import "SymbolTable.h"
#include "ConnectCommand.h"

int SetVarCommand::exec(vector<string> params) {
  SymbolTable &symblTbl = SymbolTable::getInstance();

  string name = params[0];
  double value = stod(params[1]);
  symblTbl.updateTable(name, "", value, "setVar");

  return numParams;
}