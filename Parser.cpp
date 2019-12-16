//
// Created by eyal on 16/12/19.
//

#include <iostream>
#include "Parser.h"
#include "Command.h"
#include "map"

using namespace std;

/**
 * runCommands: Runs each command in the input vector
 */
void Parser::runCommands() {
  int index = 0;
  while(index < this->inputVector.size()) {
    Command* c = this->commandMap.find(this->inputVector[index])->second;
    index += c->exec();
  }
}

