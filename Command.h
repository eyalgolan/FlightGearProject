//
// Created by eyal on 16/12/19.
//

#ifndef FLIGHTGEARPROJECT_COMMAND_H
#define FLIGHTGEARPROJECT_COMMAND_H

#include "vector"
#include "string"

using namespace std;

class Command {
 public:
  virtual int exec(vector<string> params) {}
};

#endif //FLIGHTGEARPROJECT_COMMAND_H
