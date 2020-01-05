//
// Created by eyal on 26/12/19.
//

#ifndef FLIGHTGEARPROJECT_PRINTCOMMAND_H
#define FLIGHTGEARPROJECT_PRINTCOMMAND_H

#include "Command.h"

class PrintCommand : public Command {
 private:
  int numParams = 2; //how much to advance in the Parser's input vector
 public:
  int exec(vector<string> params) override;
};

#endif //FLIGHTGEARPROJECT_PRINTCOMMAND_H
