//
// Created by eyal on 16/12/19.
//

#ifndef FLIGHTGEARPROJECT_DEFINEVARCOMMAND_H
#define FLIGHTGEARPROJECT_DEFINEVARCOMMAND_H

#include "Command.h"
using namespace std;

class DefineVarCommand : public Command {
 private:
  int numParams = 6; //how much to advance in the Parser's input vector
 public:
  int exec(vector<string> params) override;
};

#endif //FLIGHTGEARPROJECT_DEFINEVARCOMMAND_H
