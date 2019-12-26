//
// Created by eyal on 19/12/19.
//

#include "SymbolTable.h"
#include "mutex"

mutex g_updateLock;

void SymbolTable::setNameMap(string name, string sim, double value) {

  this->nameMap.insert({name, make_pair(sim, value)});
}
void SymbolTable::setSimMap(string sim, string name, double value) {
  this->simMap.insert({sim, make_pair(name, value)});
}
void SymbolTable::update(string name, string sim, double value) {
  g_updateLock.lock();
  this->nameMap.insert({name, make_pair(sim, value)});
  this->simMap.insert({sim, make_pair(name, value)});
  g_updateLock.unlock();
}