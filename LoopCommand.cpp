//
// Created by eyal on 16/12/19.
//

#include "LoopCommand.h"
#include "SymbolTable.h"

int LoopCommand::exec(vector<string> params) {
    SymbolTable &symblTbl = SymbolTable::getInstance();
    Parser loopParser(params);
    int i=1;
    double varValue;
    symblTbl.g_updateLock.lock();
    if(symblTbl.getNameMap().find(params[i]) != symblTbl.getNameMap().end()){
      varValue = symblTbl.getNameMap()[params[i]].second.first;
    }
    else {
      varValue = stod(params[i]);
    }
    symblTbl.g_updateLock.unlock();
    string con=params[i+1];
    double value =stod(params[i+2]);
    ConditionParser *cp = new ConditionParser(varValue, con, value);
    while(cp->condition) {
      loopParser.runCommands();
    }
}