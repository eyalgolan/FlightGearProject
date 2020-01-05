//
// Created by eyal on 26/12/19.
//

#include "PrintCommand.h"
#include "iostream"
#include "SymbolTable.h"
#include "ExpressionHandler.h"
/**
 * Function: PrintCommand
 * the PrintCommand have to print options
 * the first one print the sring that givven in the scope
 * evaluate the value of the given parameter, in the scope.
 * @param params: exec(vector<string> params)/
 * @return int that represent the jump tu the parser pointer.
 */
int PrintCommand::exec(vector<string> params) {
  SymbolTable &symblTbl = SymbolTable::getInstance();
  int start_pos = 0;
  string testInput = params[0];
  //check if we have \" char in the print command
  if ((start_pos = testInput.find("\"", start_pos)) != string::npos) {
    start_pos = 0;
    while ((start_pos = params[0].find("(", start_pos))
        != string::npos) {
      params[0].replace(start_pos, 1, "");
      start_pos += 0;
    }
    start_pos = 0;
    // replace the ")" char to  ""
    while ((start_pos = params[0].find(")", start_pos))
        != string::npos) {
      params[0].replace(start_pos, 1, "");
      start_pos += 0;
    }
    start_pos = 0;
    // replace the /" char to  ""
    while ((start_pos = params[0].find("\"", start_pos))
        != string::npos) {
      params[0].replace(start_pos, 1, "");
      start_pos += 0;
    }
    cout << params[0] << endl;
  } else {
    // if we not have " in the print scope
    int start_pos = 0;
    while ((start_pos = params[0].find(" ", start_pos)) != string::npos) {
      params[0].replace(start_pos, 1, "");
      start_pos += 0;
    }
    // set the Interpreter
    double input;
    Interpreter *inPrint = new Interpreter();
    Expression *expPrint = nullptr;
    symblTbl.g_updateLock.lock();
    string toSet = symblTbl.getSetExp();
    symblTbl.g_updateLock.unlock();
    inPrint->setVariables(toSet);
    try {
      //evaluate
      expPrint = inPrint->interpret(params[0]);
      input = expPrint->calculate();
      cout << input << endl;
    }
    catch (const char *e) {
    }
  }
  return this->numParams;
}