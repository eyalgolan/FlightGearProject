//
// Created by eyal on 16/12/19.
//

#include "DefineVarCommand.h"
#include "SymbolTable.h"
#include "iostream"

using namespace std;

int DefineVarCommand::exec(vector<string> params) {
  SymbolTable &symblTbl = SymbolTable::getInstance();

  string name = params[0];
  string simPath = params[3];
  //auto dammy=symblTbl.getSimMap().find(simPath);
  string origName = symblTbl.getSimMap().find(simPath)->second.first;
  double origValue = symblTbl.getSimMap().find(simPath)->second.second;
  symblTbl.getNameMap().erase(origName);
  symblTbl.setNameMap(name, simPath, origValue);
  symblTbl.getSimMap().find(simPath)->second.first=name;

  //symblTbl.setNameMap(name, sim, value);
  //symblTbl.setSimMap(sim, name, value);
  return this->numParams;
}