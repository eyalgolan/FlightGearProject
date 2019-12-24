//
// Created by eyal on 16/12/19.
//

#ifndef FLIGHTGEARPROJECT_CONNECTCOMMAND_H
#define FLIGHTGEARPROJECT_CONNECTCOMMAND_H

#include "Command.h"
using namespace std;

class ConnectCommand : public Command {
 private:
  int numParams = 3;
 public:
  int exec(vector<string> params) override;
};

#endif //FLIGHTGEARPROJECT_CONNECTCOMMAND_H
