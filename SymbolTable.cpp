//
// Created by eyal on 19/12/19.
//

#include <iostream>
#include "SymbolTable.h"
#include "mutex"


/**
* Function name: getSetExp
* Function generates a string in the format: "key=value;" of all the
* variables that are currently saved by the SymbolTable.
* The function's output is later used as input for ExpressionHandler's SetVar
*/
string SymbolTable::getSetExp() {
  string toSet;
  for (auto it = this->nameMap.begin(); it != this->nameMap.end(); it++) {
    toSet += it->first + "=" + to_string(it->second.second) + ";";
  }
  for (auto varIt = this->varMap.begin(); varIt != this->varMap.end();
       varIt++) {
    toSet += varIt->first + "=" + to_string(varIt->second) + ";";
  }
  return toSet;
}

/**
* Function: isInNameMap
* Receives a string input and returns if it's a key in the nameMap
*/
bool SymbolTable::isInNameMap(string name) {
  if (this->nameMap.find(name) != this->nameMap.end()) {
    return true;
  }
  return false;
}

/**
 * Function: isInSimMap
 * Receives a string input and returns if it's a key in the simMap
 */
bool SymbolTable::isInSimMap(string sim) {
  if (this->simMap.find(sim) != this->simMap.end()) {
    return true;
  }
  return false;
}

/**
 * Function: isInVarMap
 * Receives a string input and returns if it's a key in the varMap
 */
bool SymbolTable::isInVarMap(string name) {

  if (this->varMap.find(name) != this->varMap.end()) {
    return true;
  }
  return false;
}

/**
 * Function: addToVarMap
 * Receives a string, double input and adds it as key, value to the varMap
 */
void SymbolTable::addToVarMap(string name, double value) {
  this->varMap.insert(make_pair(name, value));
}

/**
 * Function: getNameMapSim
 * Receives a name in the name map and returns it's sim
 */
string SymbolTable::getNameMapSim (string name) {
  string sim = this->nameMap[name].first;
  return sim;
}

/**
 * Function: getNameMapValue
 * Receives a name in the name map and returns it's value
 */
double SymbolTable::getNameMapValue(string name) {
  double value = this->nameMap[name].second;
  return value;
}

/**
 * Function: getVarMapValue
 * Receives a name in the name map and returns it's value
 */
double SymbolTable::getVarMapValue(string name) {
  double value = this->varMap[name];
  return value;
}

/**
 * Function: isQueueEmpty
 * Returns if the Command queue is empty
 */
bool SymbolTable::isQueueEmpty() {
  return this->commandsToSimulator.empty();
}

/**
 * Function: getFirstInQueue
 * Returns the first command in the command queue
 */
string SymbolTable::getFirstInQueue() {
  return this->commandsToSimulator.front();
}

/**
 * Function: pushToQueue
 * Push a new command to the command queue
 */
void SymbolTable::pushToQueue(string command) {
  this->commandsToSimulator.push(command);
}

/**
 * Function: popFromQueue
 * Pops a command from the command queue
 */
void SymbolTable::popFromQueue() {
  this->commandsToSimulator.pop();
}

/**
 * Function: insertToNameMap
 * Inserts a new (name, (sim, value)} to the name map
 */
void SymbolTable::insertToNameMap(string name, string sim, double value) {
  this->nameMap.insert({name, make_pair(sim, value)});
}

/**
 * Function: insertToSimMap
 * Inserts a new (sim, (name, value)} to the sim map
 */
void SymbolTable::insertToSimMap(string sim, string name, double value) {
  this->simMap.insert({sim, make_pair(name, value)});
}

/**
 * Function: updateTable
 * Function is called from different commands, and calls the appropriate
 * "UpdateFrom" function according to the command who called it
 */
void SymbolTable::updateTable(string name,
                              string sim,
                              double value,
                              string calledFrom) {

  //checks who called the function and calls the appropriate "UpdateFrom" func
  if (calledFrom.compare("server") == 0) {
    updateFromServer(name, sim, value);
  } else if (calledFrom.compare("defineVar") == 0) {
    updateFromDefineVar(name, sim, value);
  } else if (calledFrom.compare("setVar") == 0) {
    updateFromSetVar(name, sim, value);
  }
}

/**
 * Function: updateFromServer
 * Updates the name & sim maps according to data received from the simulator
 * Locks the symbol table's lock while updating
 */
void SymbolTable::updateFromServer(string name, string sim, double value) {
  g_updateLock.lock();

  // erases old entries in the maps and creates new ones with updated data
  string origName = this->simMap[sim].first; //gets the original name
  this->nameMap.erase(origName);
  this->nameMap.insert({origName, make_pair(sim, value)});
  this->simMap.erase(sim);
  this->simMap.insert({sim, make_pair(origName, value)});

  g_updateLock.unlock();
}

/**
 * Function: updateFromDefineVar
 * Updates the name & sim maps with a new var name
 */
void SymbolTable::updateFromDefineVar(string name, string sim, double value) {
  g_updateLock.lock();
  string origName = this->simMap[sim].first; //gets the original name
  double origValue = this->simMap[sim].second; //gets the original value

  // erases old entries in the maps and creates new ones with updated var name
  this->nameMap.erase(origName);
  this->insertToNameMap(name, sim, origValue);
  this->simMap.erase(sim);
  this->insertToSimMap(sim, name, origValue);
  g_updateLock.unlock();
}

/**
 * Function: updateFromSetVar
 * Updates the name & sim maps with a new value
 */
void SymbolTable::updateFromSetVar(string name, string sim, double value) {
  g_updateLock.lock();
  this->nameMap[name].second = value;
  sim = this->nameMap[name].first;
  this->simMap[sim].second = value;
  g_updateLock.unlock();
}