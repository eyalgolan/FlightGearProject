//
// Created by eyal on 16/12/19.
//

#include "LoopCommand.h"
#include "SymbolTable.h"

int LoopCommand::exec(vector<string> params) {
    vector<string> whileParams;
    for(int j = 4; j < params.size() ; j++) {
        whileParams.push_back(params[j]);
        //cout<<"getting " + params[j] + " to while parser"<<endl;
    }
    Parser loopParser(whileParams);
    int i=0;
    string firstExp = params[i];
    string con=params[i+1];
    string secondExp = params[i+2];
    vector<string> conditionVector;
    conditionVector.push_back(firstExp);
    conditionVector.push_back(con);
    conditionVector.push_back(secondExp);
    ConditionParser *cp = new ConditionParser();
    cp->exec(conditionVector);
    while(cp->condition) {
      loopParser.runCommands();
      cp->exec(conditionVector);
    }
    return 0;
}