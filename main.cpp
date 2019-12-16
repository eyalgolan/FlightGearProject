#include <iostream>
#include "Lexer.h"
#include "Parser.h"
using namespace std;

int main() {
  Lexer l("/home/eyal/Desktop/AP1/FlightGearProject/fly.txt");
  Parser p(l);
  return 0;

}