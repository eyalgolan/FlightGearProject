//
// Created by eyal on 16/12/19.
//

#ifndef FLIGHTGEARPROJECT_CONDITIONPARSER_H
#define FLIGHTGEARPROJECT_CONDITIONPARSER_H

#include "Command.h"

using namespace std;

class ConditionParser : public Command {
 public:
  bool condition;     // indicates if the condition is met or not
  int numParams = 3;  //how much to advance in the Parser's input vector
  int exec(vector<string> params) override;
};

#endif //FLIGHTGEARPROJECT_CONDITIONPARSER_H
