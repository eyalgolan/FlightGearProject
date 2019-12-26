//
// Created by eyal on 26/12/19.
//

#include "SleepCommand.h"
#include "unistd.h"
using namespace std;

int SleepCommand::exec(vector<string> params) {
  int time = stoi(params[0]);
  auto unsignedTime = (unsigned int)time;
  sleep(unsignedTime);
  return numParams;
}