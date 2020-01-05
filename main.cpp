#include <iostream>
#include "Lexer.h"
#include "Parser.h"
#include "SymbolTable.h"

#include <sys/socket.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <algorithm>

using namespace std;
/**
 * @param argc
 * @param argv  we get the file name that containe txt file that we want to
 * use for the project.
 * @return  int.
 */
int main(int argc, char **argv) {
/**
 * sendind the file to the lexer that give us a vector
 * in this project we also  need to "compile" new programing languish
 * so we get the txt file send it to the lexer and then send the givven
 * vector from the lexer to thr parser.
 * but because we have free space syntax we need handel the "print"
 * that need have a space in some case
 * before we send it to the parser command;
 */
  char *input_file = argv[1]; // get the filename
  Lexer l(input_file);        //send it to the lexer
  vector<string> emulateLexerResulttest = l.getvecor();
  vector<string> notspace;
  int i = 0;
  SymbolTable &symblTbl = SymbolTable::getInstance();
  while (i < emulateLexerResulttest.size()) {
/**
 * we delete all aspace from all the vector if they dont gave print command before;
 */
    string toLex = emulateLexerResulttest[i];
    if (toLex.compare("Print") == 0) {
      notspace.push_back(emulateLexerResulttest[i]);
      i++;
      size_t n = count(emulateLexerResulttest[i].begin(), emulateLexerResulttest[i].end(), '\"');
      if (n==2) {
        notspace.push_back(emulateLexerResulttest[i]);
        i++;
      }
      else if (n==1) {

        string chaining="";
        while (n!=2){
          chaining += emulateLexerResulttest[i];
          i++;
          n=n+count(emulateLexerResulttest[i].begin(), emulateLexerResulttest[i].end(), '\"');

        }
        chaining += emulateLexerResulttest[i];
        notspace.push_back(chaining);
        i++;
      }
      else if (n==0){
        notspace.push_back(emulateLexerResulttest[i]);
        i++;
//        notspace.push_back(emulateLexerResulttest[i]);
//        i++;
      }
    } else if (emulateLexerResulttest[i].compare("print") != 0) {
      int start_pos = 0;
      while ((start_pos = emulateLexerResulttest[i].find(" ", start_pos))
          != string::npos) {
        emulateLexerResulttest[i].replace(start_pos, 1, "");
        start_pos += 0; // Handles case where 'to' is a substring of 'from'
      }
      notspace.push_back(emulateLexerResulttest[i]);
      i++;
    }

  }
  // sending the vector to the parser
  Parser p(notspace);
  // run the command
  p.runCommands();

  return 0;

}