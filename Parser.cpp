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
#include "SymbolTable.h"
#include "ExpressionHandler.h"
#include "Expression.h"
#include "chrono"
#include "thread"


using namespace std;

/**
 * runCommands: Runs each command in the input vector
 */
void Parser::runCommands() {
    int index = 0;
    vector<string> inputParams;

    while(index < this->inputVector.size()) {
        Command* c;

        string commandName;
        string input;
        if(this->inputVector[index] == "}"){
            break;
        }
        else if(this->commandMap.find(this->inputVector[index]) != this->commandMap.end()) {
            c = this->commandMap.find(this->inputVector[index])->second;
            commandName = this->inputVector[index];
            if (c != nullptr) {
                if (commandName.compare("openDataServer") == 0) {
                    Interpreter *inOp = new Interpreter();
                    Expression* expOp = nullptr;
                    expOp = inOp->interpret(inputVector[index + 1]);
                    input = to_string((int)expOp->calculate());
                    //cout<<input<<endl;
                    inputParams.push_back(input);
                    //cout << commandName << endl;
                    index += c->exec(inputParams);
                    inputParams.clear();
                } else if (commandName.compare("while") == 0) {
                    while (inputVector[index+1]!="}") {
                        index++;
                        inputParams.push_back(inputVector[index]);
                    }
                    index+=2;
                    index+=c->exec(inputParams);
                    inputParams.clear();
                } else if (commandName.compare("if") == 0) {
                    while (inputVector[index+1]!="}") {
                        index++;
                        inputParams.push_back(inputVector[index]);
                    }
                    index+=2;
                    index+=c->exec(inputParams);
                    inputParams.clear();
                } else if (commandName.compare("connectControlClient") == 0) {
                    inputParams.push_back(inputVector[index + 1]);

                    Interpreter *inCon = new Interpreter();
                    Expression* expCon = nullptr;
                    expCon = inCon->interpret(inputVector[index + 2]);
                    input = to_string((int)expCon->calculate());
                    cout<<input<<endl;
                    inputParams.push_back(input);
                    //cout << commandName << endl;
                    index += c->exec(inputParams);
                    inputParams.clear();
                } else if (commandName.compare("Print") == 0) {
                    //cout << "try print command" << endl;
                    inputParams.push_back(inputVector[index + 1]);
                    //cout << commandName << endl;
                    index += c->exec(inputParams);
                    inputParams.clear();
                } else if (commandName.compare("var") == 0
                           && inputVector[index + 2].compare("=") != 0) {
                    inputParams.push_back(inputVector[index + 1]);
                    inputParams.push_back(inputVector[index + 5]);
                    //cout << commandName << endl;
                    index += c->exec(inputParams);
                    inputParams.clear();
                    //  cout<<"I'm in var command"<<endl;
                }
                else if(commandName.compare("var") == 0
                    && inputVector[index + 2].compare("=") == 0) {
                    inputParams.push_back(inputVector[index + 1]);
                    inputParams.push_back(inputVector[index + 2]);
                    inputParams.push_back(inputVector[index + 3]);
                    //cout << commandName << endl;
                    c = this->commandMap.find("assignVar")->second;
                    index += c->exec(inputParams);
                    inputParams.clear();
                }
                else if (commandName.compare("Sleep") == 0) {
                    Interpreter *inSleep = new Interpreter();
                    Expression* expSleep = nullptr;
                    SymbolTable &symblTbl = SymbolTable::getInstance();
                    string toSet = symblTbl.getSetExp();
                    inSleep->setVariables(toSet);
                    expSleep = inSleep->interpret(inputVector[index + 1]);
                    input = to_string(expSleep->calculate());
                    inputParams.push_back(input);
                    //cout << commandName << endl;
                    index += c->exec(inputParams);
                    inputParams.clear();
                }
            }
        }
        else {
            commandName = this->inputVector[index];
            //cout<<"didn't identify command"<<endl;
            //cout<<commandName<<endl;
            c = this->commandMap.find("setVarCommand")->second;
            inputParams.push_back(inputVector[index]);
            inputParams.push_back(inputVector[index+2]);
            //cout<<commandName<<endl;
            index += c->exec(inputParams);
            inputParams.clear();
            this_thread::sleep_for(chrono::milliseconds(500));
        }
    }
}
