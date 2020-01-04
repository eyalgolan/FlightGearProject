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
  string dammyp=params[0];
  //removing all the space;
  while ((start_pos = dammyp.find(" ", start_pos)) != string::npos)
  {
    dammyp.replace(start_pos, 1, "");
    start_pos += 0;
  }
    if(symblTbl.isInNameMap(dammyp)||symblTbl.isInVarMap(dammyp)){
      int start_pos = 0;
      while ((start_pos = params[0].find(" ", start_pos)) != string::npos)
      {
        params[0].replace(start_pos, 1, "");
        start_pos += 0;
      }
    }
    // using the interpreter to evaluate the parm
  string inputd;
  Interpreter *inPrintd = new Interpreter();
  Expression* expPrintd = nullptr;
  string toSetd = symblTbl.getSetExp();
  inPrintd->setVariables(toSetd);
  try {
    expPrintd = inPrintd->interpret(dammyp);
    int start_pos = 0;
    while ((start_pos = params[0].find(" ", start_pos)) != string::npos)
    {
      params[0].replace(start_pos, 1, "");
      start_pos += 0; // Handles case where 'to' is a substring of 'from'
    }
  }
  catch (const char* e) {
  }

    string input;
    Interpreter *inPrint = new Interpreter();
    Expression* expPrint = nullptr;
    string toSet = symblTbl.getSetExp();
    inPrint->setVariables(toSet);
    try {
      expPrint = inPrint->interpret(params[0]);
      input = to_string((int) expPrint->calculate());
      cout<<input<<endl;
    }
    catch (const char* e) {
      cout<<params[0]<<endl;
    }

  return this->numParams;
}