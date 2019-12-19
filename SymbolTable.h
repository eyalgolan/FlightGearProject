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
  static SymbolTable& getInstance() {
    static SymbolTable instance;
    return instance;
  }
  map<string, pair<string, double>> getNameMap() {
    return this->nameMap;
  }
  map<string, pair<string, double>> getSimMap() {
    return this->simMap;
  }
  void setNameMap(string name, string sim, double value);
  void setSimMap(string sim, string name, double value);

  SymbolTable(SymbolTable const&) = delete;
  void operator=(SymbolTable const&) = delete;
 private:
  SymbolTable(){}
  map<string, pair<string, double>> nameMap;
  map<string, pair<string, double>> simMap;

};
#endif //FLIGHTGEARPROJECT_SYMBOLTABLE_H
