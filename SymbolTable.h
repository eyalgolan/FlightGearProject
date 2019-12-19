//
// Created by eyal on 19/12/19.
//

#ifndef FLIGHTGEARPROJECT_SYMBOLTABLE_H
#define FLIGHTGEARPROJECT_SYMBOLTABLE_H

#import "map"
#import "string"
using namespace std;

class SymbolTable {
 public:
  map<string, pair<double, string>> controlVars;
  map<string, pair<double, string>> instrumentationVars;

};
#endif //FLIGHTGEARPROJECT_SYMBOLTABLE_H
