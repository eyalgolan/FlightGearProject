//
// Created by eyal on 16/12/19.
//

#include "LoopCommand.h"
#include "SymbolTable.h"

/**
 * Function: exec
 * Exectutes the commands in the Loop's scope while the loop's condition is met
 * @param params a vector containing all the commands in the loop's scope
 * @return how much to advance in the Parser's input vector
 */
int LoopCommand::exec(vector<string> params) {

  //gets all commands in loop's scope
  vector<string> whileParams;
  for (int j = 4; j < params.size(); j++) {
    whileParams.push_back(params[j]);
  }

  //initialize a parser with the loop's commands
  Parser loopParser(whileParams);

  //evaluate if the loop condition is met
  string firstExp = params[0];
  string con = params[1];
  string secondExp = params[2];
  vector<string> conditionVector;
  conditionVector.push_back(firstExp);
  conditionVector.push_back(con);
  conditionVector.push_back(secondExp);
  ConditionParser *cp = new ConditionParser();
  cp->exec(conditionVector);

  //while the loop condition is met, run the commands in the loop's scope
  while (cp->condition) {
    loopParser.runCommands();
    cp->exec(conditionVector); //evaluate if the loop condition is met
  }
  return this->numParams;
}