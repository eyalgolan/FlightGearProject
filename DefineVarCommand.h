//
// Created by eyal on 16/12/19.
//

#ifndef FLIGHTGEARPROJECT_DEFINEVARCOMMAND_H
#define FLIGHTGEARPROJECT_DEFINEVARCOMMAND_H

#include "Command.h"
using namespace std;

class DefineVarCommand : public Command {
 private:
  int numParams = 1;
 public:
  int exec() override;
};

#endif //FLIGHTGEARPROJECT_DEFINEVARCOMMAND_H
