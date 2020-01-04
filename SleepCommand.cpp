//
// Created by eyal on 26/12/19.
//

#include "SleepCommand.h"
#include "unistd.h"
#include "iostream"
#include "chrono"
#include "thread"

using namespace std;
/**
 * set sleep that give us from the param;
 * @param params
 * @return how much to advance in the input vector
 */
int SleepCommand::exec(vector<string> params) {
  int time = stoi(params[0]);
  this_thread::sleep_for(chrono::milliseconds(time));
  return numParams;
}