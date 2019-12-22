//
// Created by eyal on 16/12/19.
//

#include <iostream>
#include "Parser.h"
#include "Command.h"
#include "map"
#include "typeinfo"
#include <string>
#include <stdio.h>
#include <cstring>

using namespace std;

/**
 * runCommands: Runs each command in the input vector
 */
void Parser::runCommands() {
  int index = 0;
  vector<string> inputParams;
  int i = 1;
  while(index < this->inputVector.size()) {
    Command* c = this->commandMap.find(this->inputVector[index])->second;
    if(c != nullptr) {
      if(strcmp(typeid(c).name(),"OpenDataServer") != 0) {
        inputParams.push_back(inputVector[i]);
      }
      index += c->exec(inputParams);
      inputParams.clear();
    }
  }
}

