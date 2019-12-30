//
// Created by eyal on 16/12/19.
//

#include "LoopCommand.h"
#include "SymbolTable.h"

int LoopCommand::exec(vector<string> params) {
    Parser loopParser(params);
    int i=1;
    string firstExp = params[i];
    string con=params[i+1];
    string secondExp = params[i+2];
    vector<string> conditionVector;
    conditionVector.push_back(firstExp);
    conditionVector.push_back(con);
    conditionVector.push_back(secondExp);
    ConditionParser *cp = new ConditionParser(conditionVector);
    while(cp->condition) {
      loopParser.runCommands();
    }
}