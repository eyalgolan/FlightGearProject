//
// Created by eyal on 16/12/19.
//

#ifndef FLIGHTGEARPROJECT_OPENDATASERVERCOMMAND_H
#define FLIGHTGEARPROJECT_OPENDATASERVERCOMMAND_H

#include "Command.h"
#include "string"
#include <vector>

using namespace std;

class OpenServerCommand : public Command {
 private:
  int numParams = 1;
  void readFromClient(int client_socket, vector<string, pair<string, double>> xmlFormat);
 public:
  int exec(vector<string> params) override;
};

#endif //FLIGHTGEARPROJECT_OPENDATASERVERCOMMAND_H
