//
// Created by eyal on 16/12/19.
//

#ifndef FLIGHTGEARPROJECT_PARSER_H
#define FLIGHTGEARPROJECT_PARSER_H

#endif //FLIGHTGEARPROJECT_PARSER_H

#include "map"
#include "Command.h"
#include "OpenServerCommand.h"
#include "ConnectCommand.h"
#include "DefineVarCommand.h"
using namespace std;

class Parser {
 public:
  static map<string, Command*> commandMap;
  OpenServerCommand* openServerCommand = new OpenServerCommand;
  ConnectCommand* connectCommand;
  DefineVarCommand* defineVarCommand;

  Parser(){
    commandMap["openDataServer"] = openServerCommand;
    commandMap["connectControlClient"] = connectCommand;
    commandMap["var"] = defineVarCommand;
  }
  ~Parser(){}
};