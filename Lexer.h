//
// Created by eyal on 15/12/19.
//
#include <iostream>
//#include "string"
#include <vector>
using namespace std;
#ifndef FLIGHTGEARPROJECT_LEXER_H
#define FLIGHTGEARPROJECT_LEXER_H

class Lexer {
 public:
  vector<string> vect;
  string afterlerx;
  Lexer(char *filename);
  vector<string> getvecor();
  ~Lexer() {}
};

#endif //FLIGHTGEARPROJECT_LEXER_H
