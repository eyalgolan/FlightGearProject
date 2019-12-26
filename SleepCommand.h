//
// Created by eyal on 26/12/19.
//

#ifndef FLIGHTGEARPROJECT_SLEEPCOMMAND_H
#define FLIGHTGEARPROJECT_SLEEPCOMMAND_H
#include "Command.h"
class SleepCommand : public Command{
 private:
  int numParams = 2;
 public:
  int exec(vector<string> params) override;
};

#endif //FLIGHTGEARPROJECT_SLEEPCOMMAND_H
