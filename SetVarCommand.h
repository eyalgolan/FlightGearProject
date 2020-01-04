//
// Created by eyal on 24/12/19.
//

#ifndef FLIGHTGEARPROJECT_SETVARCOMMAND_H
#define FLIGHTGEARPROJECT_SETVARCOMMAND_H

#include "Command.h"
class SetVarCommand : public Command{
 private:
  int numParams = 3; //how much to advance in the Parser's input vector
 public:
  int exec(vector<string> params) override;
  void writeToQueue(string input);
};

#endif //FLIGHTGEARPROJECT_SETVARCOMMAND_H
