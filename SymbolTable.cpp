//
// Created by eyal on 19/12/19.
//

#include <iostream>
#include "SymbolTable.h"
#include "mutex"

void SymbolTable::setNameMap(string name, string sim, double value) {

  this->nameMap.insert({name, make_pair(sim, value)});
}
void SymbolTable::setSimMap(string sim, string name, double value) {
  this->simMap.insert({sim, make_pair(name, value)});
}
void SymbolTable::updateTable(string name,
                              string sim,
                              double value,
                              string calledFrom) {
  g_updateLock.lock();
  if(calledFrom.compare("server") == 0) {
    updateFromServer(name, sim, value);
  }
  else if(calledFrom.compare("defineVar") == 0) {
    updateFromDefineVar(name, sim, value);
    cout<<this->simMap[sim].first<<endl;
  }
  else if(calledFrom.compare("setVar") == 0) {
    updateFromSetVar(name, sim, value);
  }
  g_updateLock.unlock();
}
void SymbolTable::updateFromServer(string name, string sim, double value) {
    string origName = this->getSimMap()[sim].first;
    this->nameMap.insert({origName, make_pair(sim, value)});
    this->simMap.insert({sim, make_pair(origName, value)});
}
void SymbolTable::updateFromDefineVar(string name, string sim, double value) {
  string origName = this->getSimMap()[sim].first;
  double origValue = this->getSimMap()[sim].second;
  this->getNameMap().erase(origName);
  this->setNameMap(name, sim, origValue);
  this->getSimMap().erase(sim);
  this->setSimMap(sim, name, origValue);
}
void SymbolTable::updateFromSetVar(string name, string sim, double value) {
  this->getNameMap()[name].second = value;
  sim = this->getNameMap()[name].first;
  this->getSimMap()[sim].second = value;
}