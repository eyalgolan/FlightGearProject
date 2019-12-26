//
// Created by eyal on 26/12/19.
//

#include "PrintCommand.h"
#include "iostream"
#import "SymbolTable.h"

int PrintCommand::exec(vector<string> params) {
  SymbolTable &symblTbl = SymbolTable::getInstance();
  cout<<params[0]<<endl;
  symblTbl.g_updateLock.lock();
  cout<<"i'm trying to print"<<endl;
  auto it = symblTbl.getNameMap().find(params[0]);
  if(it != symblTbl.getNameMap().end()) {
    cout<<"i'm trying to print a value"<<endl;
    cout<<params[0]<<endl;
    cout<<symblTbl.getNameMap()[params[0]].first<<endl;
    cout<<symblTbl.getNameMap()[params[0]].second<<endl;
  }
  else {
    cout<<"im trying to print a plaint text"<<endl;
    cout<<params[0]<<endl;
  }
  symblTbl.g_updateLock.unlock();
  return this->numParams;
}