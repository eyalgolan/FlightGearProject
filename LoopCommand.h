//
// Created by eyal on 30/12/19.
//

#ifndef FLIGHTGEARPROJECT_LOOPCOMMAND_H
#define FLIGHTGEARPROJECT_LOOPCOMMAND_H

#include "Command.h"
#include "ConditionParser.h"
#include "iostream"

using namespace std;

class LoopCommand: public Command {
 private:
  int numParams = 0;
 public:
  int exec(vector<string> params) override;
};

#endif //FLIGHTGEARPROJECT_LOOPCOMMAND_H
