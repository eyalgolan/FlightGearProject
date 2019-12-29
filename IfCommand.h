//
// Created by eyal on 16/12/19.
//

#ifndef FLIGHTGEARPROJECT_IFCOMMAND_H
#define FLIGHTGEARPROJECT_IFCOMMAND_H

#include "Command.h"
#include "ConditionParser.h"
#include "iostream"

using namespace std;

class IfCommand: public ConditionParser {
 public:
  int exec(vector<string> params) override;
};

#endif //FLIGHTGEARPROJECT_IFCOMMAND_H
