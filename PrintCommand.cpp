//
// Created by eyal on 26/12/19.
//

#include "PrintCommand.h"
#include "iostream"
#import "SymbolTable.h"

int PrintCommand::exec(vector<string> params) {
  SymbolTable &symblTbl = SymbolTable::getInstance();
  //cout<<params[0]<<endl;
  int start_pos = 0;
  string dammyp=params[0];
  while ((start_pos = dammyp.find(" ", start_pos)) != string::npos)
  {
    dammyp.replace(start_pos, 1, "");
    start_pos += 0; // Handles case where 'to' is a substring of 'from'
  }
    if(symblTbl.isInNameMap(dammyp)){
      int start_pos = 0;
      while ((start_pos = params[0].find(" ", start_pos)) != string::npos)
      {
        params[0].replace(start_pos, 1, "");
        start_pos += 0; // Handles case where 'to' is a substring of 'from'
      }
    }
  //cout<<"i'm trying to print"<<endl;
  symblTbl.g_updateLock.lock();
  auto it = symblTbl.getNameMap().find(params[0]);
  if(symblTbl.isInNameMap(params[0])) {
    //cout<<"i'm trying to print a value"<<endl;
    //cout<<params[0]<<endl;
    //cout<<symblTbl.getNameMap()[params[0]].first<<endl;
    cout<<symblTbl.getNameMap()[params[0]].second<<endl;
  }
  else {
    //cout<<"im trying to print a plaint text"<<endl;
    cout<<params[0]<<endl;
  }
  symblTbl.g_updateLock.unlock();
  return this->numParams;
}