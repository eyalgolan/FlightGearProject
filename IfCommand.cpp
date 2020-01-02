//
// Created by eyal on 16/12/19.
//

#include "IfCommand.h"

#include "SymbolTable.h"

int IfCommand::exec(vector<string> params) {
  vector<string> ifParams;
  for(int j = 4; j < params.size() ; j++) {
    ifParams.push_back(params[j]);
    //cout<<"getting " + params[j] + " to while parser"<<endl;
  }
  Parser ifParser(ifParams);
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
  if(cp->condition) {
    ifParser.runCommands();
  }
  return 0;
}
