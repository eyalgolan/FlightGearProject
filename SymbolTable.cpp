//
// Created by eyal on 19/12/19.
//

#include <iostream>
#include "SymbolTable.h"
#include "mutex"

mutex g_updateLock;

void SymbolTable::setNameMap(string name, string sim, double value) {

  this->nameMap.insert({name, make_pair(sim, value)});
}
void SymbolTable::setSimMap(string sim, string name, double value) {
  this->simMap.insert({sim, make_pair(name, value)});
}
void SymbolTable::update(string name, string sim, double value, string calledFrom) {
  g_updateLock.lock();
  if(calledFrom.compare("server") == 0) {
    updateFromServer(name, sim, value);
  }
  else if(calledFrom.compare("client") == 0) {
    updateFromVar(name, sim, value);
    cout<<this->simMap[sim].first<<endl;
  }
  g_updateLock.unlock();
}
void SymbolTable::updateFromServer(string name, string sim, double value) {
    string origName = this->getSimMap()[sim].first;
    this->nameMap.insert({origName, make_pair(sim, value)});
    this->simMap.insert({sim, make_pair(origName, value)});
}
void SymbolTable::updateFromVar(string name, string sim, double value) {
  string origName = this->getSimMap()[sim].first;
  double origValue = this->getSimMap()[sim].second;
  this->getNameMap().erase(origName);
  this->setNameMap(name, sim, origValue);
  this->getSimMap().erase(sim);
  this->setSimMap(sim, name, origValue);
}