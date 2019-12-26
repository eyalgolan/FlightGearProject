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
#include "SetVarCommand.h"
#include "PrintCommand.h"
#include "SleepCommand.h"

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
  Command* setVarCommand;
  Command* printCommand;
  Command* sleepCommand;

  Parser(vector<string> inputFromLexer){
    inputVector = inputFromLexer;
    openServerCommand = new OpenServerCommand;
    connectCommand = new ConnectCommand;
    defineVarCommand = new DefineVarCommand;
    setVarCommand = new SetVarCommand;
    printCommand = new PrintCommand;
    sleepCommand = new SleepCommand;
    commandMap["openDataServer"] = openServerCommand;
    commandMap["connectControlClient"] = connectCommand;
    commandMap["var"] = defineVarCommand;
    commandMap["setVarCommand"] = setVarCommand;
    commandMap["Print"] = printCommand;
    commandMap["Sleep"] = sleepCommand;
  }
  ~Parser(){
    delete openServerCommand;
    delete connectCommand;
    delete defineVarCommand;
    delete setVarCommand;
    delete printCommand;
    delete sleepCommand;
  }
  void runCommands();
};

#endif //FLIGHTGEARPROJECT_PARSER_H
