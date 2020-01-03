#include <iostream>
#include "Lexer.h"
#include "Parser.h"
#include "SymbolTable.h"

#include <sys/socket.h>
#include <cstring>
#include <iostream>
#include <unistd.h>

using namespace std;

int main(int argc, char **argv) {

  char *input_file = argv[1];
  Lexer l(input_file);
  vector<string> emulateLexerResulttest=l.getvecor();
  vector<string> notspace;
  int i = 0;
  SymbolTable &symblTbl = SymbolTable::getInstance();

  while ( i < emulateLexerResulttest.size()){

      string toLex=emulateLexerResulttest[i];
      if (toLex.compare("Print")==0){
          notspace.push_back(emulateLexerResulttest[i]);
          i++;
          notspace.push_back(emulateLexerResulttest[i]);
          i++;
      }
      else if (emulateLexerResulttest[i].compare("print")!=0){
          int start_pos = 0;
          while ((start_pos = emulateLexerResulttest[i].find(" ", start_pos)) != string::npos)
          {
              emulateLexerResulttest[i].replace(start_pos, 1, "");
              start_pos += 0; // Handles case where 'to' is a substring of 'from'
          }
          notspace.push_back(emulateLexerResulttest[i]);
          i++;
      }

  }

  Parser p(notspace);
  p.runCommands();

  return 0;

}