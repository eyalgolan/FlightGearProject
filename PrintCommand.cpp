//
// Created by eyal on 26/12/19.
//

#include "PrintCommand.h"
#include "iostream"
#import "SymbolTable.h"

int PrintCommand::exec(vector<string> params) {
  SymbolTable &symblTbl = SymbolTable::getInstance();
  symblTbl.g_updateLock.lock();
  if(symblTbl.getNameMap().find(params[0]) != symblTbl.getNameMap().end()) {
    cout<<symblTbl.getNameMap()[params[0]].second<<endl;
  }
  else {
    cout<<params[0]<<endl;
  }
  symblTbl.g_updateLock.unlock();
  return this->numParams;
}