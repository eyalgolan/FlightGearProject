//
// Created by eyal on 16/12/19.
//

#ifndef FLIGHTGEARPROJECT_OPENDATASERVERCOMMAND_H
#define FLIGHTGEARPROJECT_OPENDATASERVERCOMMAND_H

#include "Command.h"
using namespace std;

class OpenServerCommand : public Command {
 private:
  int numParams = 1;
 public:
  int exec() override;
};

#endif //FLIGHTGEARPROJECT_OPENDATASERVERCOMMAND_H
