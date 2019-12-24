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
  while(index < this->inputVector.size()) {
    Command* c = this->commandMap.find(this->inputVector[index])->second;
    string commandName = this->inputVector[index];
    if(c != nullptr) {
      if(commandName.compare("openDataServer") ==0) {
        inputParams.push_back(inputVector[index+1]);
        cout<<commandName<<endl;
        index += c->exec(inputParams);
        inputParams.clear();

      }
      else if(commandName.compare("connectControlClient")==0) {
        inputParams.push_back(inputVector[index+1]);
        inputParams.push_back(inputVector[index+2]);
        cout<<commandName<<endl;
        index += c->exec(inputParams);
        inputParams.clear();
      }
      else if(commandName.compare("var") == 0 && inputVector[index+2].compare("=") != 0) {
        inputParams.push_back(inputVector[index+1]);
        inputParams.push_back(inputVector[index+2]);
        inputParams.push_back(inputVector[index+3]);
        inputParams.push_back(inputVector[index+4]);
        cout<<commandName<<endl;
        index += c->exec(inputParams);
        inputParams.clear();
      //  cout<<"I'm in var command"<<endl;
      }
//     cout<<"parser next command"<<endl;
    }
  }
}

