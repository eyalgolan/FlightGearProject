//
// Created by eyal on 26/12/19.
//

#include "PrintCommand.h"
#include "iostream"
#include "SymbolTable.h"
#include "ExpressionHandler.h"

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
    if(symblTbl.isInNameMap(dammyp)||symblTbl.isInVarMap(dammyp)){
      int start_pos = 0;
      while ((start_pos = params[0].find(" ", start_pos)) != string::npos)
      {
        params[0].replace(start_pos, 1, "");
        start_pos += 0; // Handles case where 'to' is a substring of 'from'
      }
    }
  string inputd;
  Interpreter *inPrintd = new Interpreter();
  Expression* expPrintd = nullptr;
  string toSetd = symblTbl.getSetExp();
  inPrintd->setVariables(toSetd);
  try {
    expPrintd = inPrintd->interpret(dammyp);
    int start_pos = 0;
    while ((start_pos = params[0].find(" ", start_pos)) != string::npos)
    {
      params[0].replace(start_pos, 1, "");
      start_pos += 0; // Handles case where 'to' is a substring of 'from'
    }
  }
  catch (const char* e) {
  }

    string input;
    Interpreter *inPrint = new Interpreter();
    Expression* expPrint = nullptr;
    string toSet = symblTbl.getSetExp();
    inPrint->setVariables(toSet);
    try {
      expPrint = inPrint->interpret(params[0]);
      input = to_string((int) expPrint->calculate());
      cout<<input<<endl;
    }
    catch (const char* e) {
      cout<<params[0]<<endl;
    }
//  //cout<<"i'm trying to print"<<endl;
//  //symblTbl.g_updateLock.lock();
//  auto it = symblTbl.getNameMap().find(params[0]);
//  if(symblTbl.isInNameMap(params[0])) {
//    //cout<<"i'm trying to print a value"<<endl;
//    //cout<<params[0]<<endl;
//    //cout<<symblTbl.getNameMap()[params[0]].first<<endl;
//    cout<<symblTbl.getNameMap()[params[0]].second<<endl;
//  }
//  else if(symblTbl.isInVarMap(params[0])) {
//    cout<<to_string(symblTbl.getVarMap()[params[0]])<<endl;
//  }
//  else {
//    //cout<<"im trying to print a plaint text"<<endl;
//    cout<<params[0]<<endl;
//  }
  //symblTbl.g_updateLock.unlock();
  return this->numParams;
}