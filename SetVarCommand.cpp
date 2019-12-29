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
  symblTbl.g_updateLock.lock();
  string sim = symblTbl.getNameMap()[name].first;
  symblTbl.g_updateLock.unlock();
  string command = "set " + sim + " " + params[1] + "\r\n";
  symblTbl.updateTable(name, "", value, "setVar");
  writeToQueue(command);
  return numParams;
}

void SetVarCommand::writeToQueue(string input) {
  cout<<"trying to write to queue"<<endl;
  SymbolTable &symblTbl = SymbolTable::getInstance();
  symblTbl.g_updateLock.lock();
  symblTbl.pushToQueue(input);
  symblTbl.g_updateLock.unlock();
  cout<<"success in writing to queue"<<endl;
}