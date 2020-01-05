//
// Created by eyal on 16/12/19.
//

#include "IfCommand.h"

#include "SymbolTable.h"
/**
 * Function name Ifcommand
 * Exectutes the commands in the scope while the  condition is true
 * @param params a vector containing all the commands in the  scope
 * @return how much to advance in the Parser's input vector
 */

int IfCommand::exec(vector<string> params) {
  vector<string> ifParams;
  // gets all commands in scope
  for (int j = 4; j < params.size(); j++) {
    ifParams.push_back(params[j]);
  }
  // evaluate the parameters of the conditions
  Parser ifParser(ifParams);
  string firstExp = params[0];
  string con = params[1];
  string secondExp = params[2];
  vector<string> conditionVector;
  // pushing to the vector
  conditionVector.push_back(firstExp);
  conditionVector.push_back(con);
  conditionVector.push_back(secondExp);
  ConditionParser *cp = new ConditionParser();
  cp->exec(conditionVector);
  if (cp->condition) {
    ifParser.runCommands();
  }
  return this->numParams;
}
