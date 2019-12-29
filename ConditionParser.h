//
// Created by eyal on 16/12/19.
//

#ifndef FLIGHTGEARPROJECT_CONDITIONPARSER_H
#define FLIGHTGEARPROJECT_CONDITIONPARSER_H

#include "Command.h"

using namespace std;

class ConditionParser: public Command {
 public:
  bool condition;
  int numParams = 3;
  int exec(vector<string> params) override;
  ConditionParser(double var, string op, double value);
  bool getcontidion();
  ~ConditionParser();
};

#endif //FLIGHTGEARPROJECT_CONDITIONPARSER_H
