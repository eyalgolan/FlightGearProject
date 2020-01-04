//
// Created by eyal on 16/12/19.
//

#ifndef FLIGHTGEARPROJECT_CONNECTCOMMAND_H
#define FLIGHTGEARPROJECT_CONNECTCOMMAND_H

#include "Command.h"
#include "queue"

using namespace std;

class ConnectCommand : public Command {
 private:
  int numParams = 3;//how much to advance in the Parser's input vector
 public:
  string readFromQueue();
  int exec(vector<string> params) override;
  void writeToClient(int client_socket);
};

#endif //FLIGHTGEARPROJECT_CONNECTCOMMAND_H
