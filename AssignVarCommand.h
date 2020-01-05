//
// Created by eyal on 24/12/19.
//

#ifndef FLIGHTGEARPROJECT_ASSIGNVARCOMMAND_H
#define FLIGHTGEARPROJECT_ASSIGNVARCOMMAND_H

#include "Command.h"

class AssignVarCommand : public Command {
 private:
  int numParams = 4; //how much to advance in the Parser's input vector
 public:
  int exec(vector<string> params) override;
};

#endif //FLIGHTGEARPROJECT_ASSIGNVARCOMMAND_H
