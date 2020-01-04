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
  string firstExp = params[0];
  string con=params[1];
  string secondExp = params[2];
  vector<string> conditionVector;
  conditionVector.push_back(firstExp);
  conditionVector.push_back(con);
  conditionVector.push_back(secondExp);
  ConditionParser *cp = new ConditionParser();
  cp->exec(conditionVector);
  if(cp->condition) {
    ifParser.runCommands();
  }
  return this->numParams;
}
