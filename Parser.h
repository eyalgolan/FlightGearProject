//
// Created by eyal on 16/12/19.
//

#ifndef FLIGHTGEARPROJECT_PARSER_H
#define FLIGHTGEARPROJECT_PARSER_H

#include "map"
#include "Command.h"
#include "OpenServerCommand.h"
#include "ConnectCommand.h"
#include "DefineVarCommand.h"
#include "Lexer.h"
#include "string"

using namespace std;

class Parser {
 public:
  vector<string> inputVector;
  map<string, Command*> commandMap;
  Command* openServerCommand;
  Command* connectCommand;
  Command* defineVarCommand;

  Parser(vector<string> inputFromLexer){
    inputVector = inputFromLexer;
    openServerCommand = new OpenServerCommand;
    connectCommand = new ConnectCommand;
    defineVarCommand = new DefineVarCommand;
    commandMap["openDataServer"] = openServerCommand;
    commandMap["connectControlClient"] = connectCommand;
    commandMap["var"] = defineVarCommand;
  }
  ~Parser(){
    delete openServerCommand;
    delete connectCommand;
    delete defineVarCommand;
  }
  void runCommands();
};

#endif //FLIGHTGEARPROJECT_PARSER_H
