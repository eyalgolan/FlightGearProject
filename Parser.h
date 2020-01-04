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
#include "LoopCommand.h"
#include "IfCommand.h"
#include "AssignVarCommand.h"
#include "Lexer.h"
#include "string"

using namespace std;

class Parser {
 private:

  //Data members
  vector<string> inputVector;
  map<string, Command*> commandMap;
  Command* openServerCommand;
  Command* connectCommand;
  Command* defineVarCommand;
  Command* setVarCommand;
  Command* printCommand;
  Command* sleepCommand;
  Command* loopCommand;
  Command* ifCommand;
  Command* assignVarCommand;

 public:

  /**
   * Parser's constructor
   * builds the parser's map of commands and gets the input vector
   * @param inputFromLexer: the input vector recieved from the lexer
   */
  Parser(vector<string> inputFromLexer){
    inputVector = inputFromLexer;

    //build the command map
    openServerCommand = new OpenServerCommand;
    connectCommand = new ConnectCommand;
    defineVarCommand = new DefineVarCommand;
    setVarCommand = new SetVarCommand;
    printCommand = new PrintCommand;
    sleepCommand = new SleepCommand;
    loopCommand = new LoopCommand;
    ifCommand = new IfCommand;
    assignVarCommand = new AssignVarCommand;

    commandMap["openDataServer"] = openServerCommand;
    commandMap["connectControlClient"] = connectCommand;
    commandMap["var"] = defineVarCommand;
    commandMap["setVarCommand"] = setVarCommand;
    commandMap["Print"] = printCommand;
    commandMap["Sleep"] = sleepCommand;
    commandMap["while"] = loopCommand;
    commandMap["assignVar"] = assignVarCommand;
    commandMap["if"] = ifCommand;
  }
  /**
   * Parser's deconstructor
   */
  ~Parser(){
    delete openServerCommand;
    delete connectCommand;
    delete defineVarCommand;
    delete setVarCommand;
    delete printCommand;
    delete sleepCommand;
    delete loopCommand;
    delete ifCommand;
  }
  void runCommands();
};

#endif //FLIGHTGEARPROJECT_PARSER_H
