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
#include <algorithm>
#include "SymbolTable.h"
#include "ExpressionHandler.h"
#include "Expression.h"
#include "chrono"
#include "thread"

using namespace std;

/**
 * runCommands: Runs each command in the input vector and execute it
 */
void Parser::runCommands() {

  int index = 0; // variable used to go over the inputVector
  vector<string> inputParams;

  // goes over each command
  while (index < this->inputVector.size()) {
    Command *c;

    string commandName;
    string input;

    /*
     * condition for while & if parser, checks if reached end of segment and
     * if so, breaks
     */
    if (this->inputVector[index] == "}") {
      break;
    }

      //otherwise, checks if the command is in the command map
    else if (this->commandMap.find(this->inputVector[index])
        != this->commandMap.end()) {

      //if so, gets the command object from the command map
      c = this->commandMap.find(this->inputVector[index])->second;
      commandName = this->inputVector[index];

      if (c != nullptr) {
        //if the command is openDataServer
        if (commandName.compare("openDataServer") == 0) {

          //interprets the input parameters
          Interpreter *inOp = new Interpreter();
          Expression *expOp = nullptr;
          expOp = inOp->interpret(inputVector[index + 1]);
          input = to_string((int) expOp->calculate());

          //executes OpenServerCommand with the interpreted parameters
          inputParams.push_back(input);
          index += c->exec(inputParams);
          inputParams.clear();
        }

          //otherwise, if the command is while
        else if (commandName.compare("while") == 0) {

          //gets all the commands in the while segment
          while (inputVector[index + 1] != "}") {
            index++;
            inputParams.push_back(inputVector[index]);
          }
          index += 2;

          //executes the while command
          index += c->exec(inputParams);
          inputParams.clear();
        }

          //otherwise, if the command is if
        else if (commandName.compare("if") == 0) {

          //gets all the commands in the if segment
          while (inputVector[index + 1] != "}") {
            index++;
            inputParams.push_back(inputVector[index]);
          }
          index += 2;

          //executes the if command
          index += c->exec(inputParams);
          inputParams.clear();
        }

          // otherwise, if the command is connectControlClient
        else if (commandName.compare("connectControlClient") == 0) {
          inputParams.push_back(inputVector[index + 1]);
          size_t start_pos = 0;
          // add a comma in relevant place
          while ((start_pos = inputParams[0].find("(", start_pos))
              != string::npos) {
            inputParams[0].replace(start_pos, 1, "");
            start_pos += 0;
          }
          start_pos = 0;
          // add a comma in relevant place
          while ((start_pos = inputParams[0].find("\"", start_pos))
              != string::npos) {
            inputParams[0].replace(start_pos, 1, "");
            start_pos += 0;
          }
          //interprets the input parameters
          Interpreter *inCon = new Interpreter();
          Expression *expCon = nullptr;
          start_pos = 0;
          // add a comma in relevant place
          while ((start_pos = inputVector[index + 2].find(")", start_pos))
              != string::npos) {
            inputVector[index + 2].replace(start_pos, 1, "");
            start_pos += 0;
          }
          expCon = inCon->interpret(inputVector[index + 2]);
          input = to_string((int) expCon->calculate());
          inputParams.push_back(input);



          //executes connectControlClient with the interpreted parameters
          index += c->exec(inputParams);
          inputParams.clear();
        }

          // otherwise, if the command is Print
        else if (commandName.compare("Print") == 0) {
          //executes Print with it's parameter
          inputParams.push_back(inputVector[index + 1]);
          index += c->exec(inputParams);
          inputParams.clear();
        }

          // otherwise, if the command is a DefineVar command
        else if (commandName.compare("var") == 0
            && inputVector[index + 2].compare("=") != 0) {
          size_t start_pos = 0;
          // add a comma in relevant place
          while ((start_pos = inputVector[index + 5].find('(', start_pos))
              != string::npos) {
            inputVector[index + 5].replace(start_pos, 1, "");
            start_pos += 0;
          }
          start_pos = 0;
          // add a comma in relevant place
          while ((start_pos = inputVector[index + 5].find(')', start_pos))
              != string::npos) {
            inputVector[index + 5].replace(start_pos, 1, "");
            start_pos += 0;
          }
          start_pos = 0;
          // add a comma in relevant place
          while ((start_pos = inputVector[index + 5].find('\"', start_pos))
              != string::npos) {
            inputVector[index + 5].replace(start_pos, 1, "");
            start_pos += 0;
          }
          //executes DefineVar with it's parameters
          inputParams.push_back(inputVector[index + 1]);
          inputParams.push_back(inputVector[index + 5]);

          index += c->exec(inputParams);
          inputParams.clear();
        }

          // otherwise, if the command is a AssignVar command
        else if (commandName.compare("var") == 0
            && inputVector[index + 2].compare("=") == 0) {

          //executes AssignVar with it's parameters
          inputParams.push_back(inputVector[index + 1]);
          inputParams.push_back(inputVector[index + 2]);
          inputParams.push_back(inputVector[index + 3]);
          c = this->commandMap.find("assignVar")->second;
          index += c->exec(inputParams);
          inputParams.clear();
        }

          // otherwise, if the command is a Sleep command
        else if (commandName.compare("Sleep") == 0) {

          /*
           * interprets the input parameters
           */
          Interpreter *inSleep = new Interpreter();
          Expression *expSleep = nullptr;
          //in case command was sleep(rudder)
          SymbolTable &symblTbl = SymbolTable::getInstance();
          string toSet = symblTbl.getSetExp();
          inSleep->setVariables(toSet);
          expSleep = inSleep->interpret(inputVector[index + 1]);
          input = to_string(expSleep->calculate());

          //executes Sleep with the interpreted parameters
          inputParams.push_back(input);
          index += c->exec(inputParams);
          inputParams.clear();
        }
      }
    }

      // otherwise, the command is a setVar command
    else {
      commandName = this->inputVector[index];
      c = this->commandMap.find("setVarCommand")->second;
      //executes SetVar with it's parameter
      inputParams.push_back(inputVector[index]);
      inputParams.push_back(inputVector[index + 2]);
      index += c->exec(inputParams);
      inputParams.clear();
      //sleep between setVar commands to help the plane fly
      this_thread::sleep_for(chrono::milliseconds(500));
    }
  }
}
