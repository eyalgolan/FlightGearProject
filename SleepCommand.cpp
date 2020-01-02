//
// Created by eyal on 26/12/19.
//

#include "SleepCommand.h"
#include "unistd.h"
#include "iostream"
#include "chrono"
#include "thread"

using namespace std;

int SleepCommand::exec(vector<string> params) {
  int time = stoi(params[0]);
  //cout<<"trying to sleep"<<endl;
  this_thread::sleep_for(chrono::milliseconds(time));
  //cout<<"after sleep"<<endl;
  return numParams;
}