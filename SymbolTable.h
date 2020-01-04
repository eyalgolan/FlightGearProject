//
// Created by eyal on 19/12/19.
//

#ifndef FLIGHTGEARPROJECT_SYMBOLTABLE_H
#define FLIGHTGEARPROJECT_SYMBOLTABLE_H

#include "map"
#include "string"
#include "Parser.h"
#include "mutex"
#include "queue"
#include "string"

using namespace std;

/*
 * SymbolTable: A singleton class responsible for saving the state of the plane
 */
class SymbolTable {
 public:
  mutex g_updateLock;
  static SymbolTable &getInstance() {
    static SymbolTable instance;
    return instance;
  }

  /*
   * Function name: getSetExp
   * Function generates a string in the format: "key=value;" of all the
   * variables that are currently saved by the SymbolTable.
   * The function's output is later used as input for ExpressionHandler's SetVar
   */
  string getSetExp() {
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

  /*
   * Function: isInNameMap
   * Receives a string input and returns if it's a key in the nameMap
   */
  bool isInNameMap(const string name) {
    if (this->nameMap.find(name) != this->nameMap.end()) {
      return true;
    }
    return false;
  }

  /*
   * Function: isInSimMap
   * Receives a string input and returns if it's a key in the simMap
   */
  bool isInSimMap(const string sim) {
    if (this->simMap.find(sim) != this->simMap.end()) {
      return true;
    }
    return false;
  }

  /*
   * Function: isInVarMap
   * Receives a string input and returns if it's a key in the varMap
   */
  bool isInVarMap(const string name) {

    if (this->varMap.find(name) != this->varMap.end()) {
      return true;
    }
    return false;
  }

  /*
   * Function: addToVarMap
   * Receives a string, double input and adds it as key, value to the varMap
   */
  void addToVarMap(string name, double value) {
    this->varMap.insert(make_pair(name, value));
  }

  /*
   * FUnction:
   */
  string getNameMapSim (const string name) {
    string sim = this->nameMap[name].first;
    return sim;
  }
  double getNameMapValue(const string name) {
    double value = this->nameMap[name].second;
    return value;
  }
  queue<string> getQueue() {
    return this->commandsToSimulator;
  }
  void pushToQueue(string command) {
    this->commandsToSimulator.push(command);
  }
  void popFromQueue() {
    this->commandsToSimulator.pop();
  }
  void setNameMap(string name, string sim, double value);
  void setSimMap(string sim, string name, double value);
  void updateTable(string name, string sim, double value, string calledFrom);
  SymbolTable(SymbolTable const &) = delete;
  void operator=(SymbolTable const &) = delete;
 private:
  void updateFromServer(string name, string sim, double value);
  void updateFromDefineVar(string name, string sim, double value);
  void updateFromSetVar(string name, string sim, double value);
  SymbolTable() {
    string buffer =
        "1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1";
    string names[36] =
        {"default1", "default2", "default3", "default4", "default5", "default6",
         "default7", "default8", "default9", "default10", "default11",
         "default12", "default13", "default14", "default15", "default16",
         "default17", "default18", "default19", "default20", "default21",
         "default22", "default23", "default24", "default25", "default26",
         "default27", "default28", "default29", "default30", "default31",
         "default32", "default33", "default34", "default35", "default36"};

    string sims[36] = {"/instrumentation/airspeed-indicator/indicated-speed-kt",
                       "/sim/time/warp", "/controls/switches/magnetos",
                       "/instrumentation/heading-indicator/offset-deg",
                       "/instrumentation/altimeter/indicated-altitude-ft",
                       "/instrumentation/altimeter/pressure-alt-ft",
                       "/instrumentation/attitude-indicator/indicated-pitch-deg",
                       "/instrumentation/attitude-indicator/internal-pitch-deg",
                       "/instrumentation/attitude-indicator/internal-roll-deg",
                       "instrumentation/attitude-indicator/internal-pitch-deg",
                       "/instrumentation/attitude-indicator/internal-roll-deg",
                       "/instrumentation/encoder/indicated-altitude-ft",
                       "/instrumentation/encoder/pressure-alt-ft",
                       "/instrumentation/gps/indicated-altitude-ft",
                       "/instrumentation/gps/indicated-ground-speed-kt",
                       "/instrumentation/heading-indicator/indicated-heading-deg",
                       "/instrumentation/magnetic-compass/indicated-heading-deg",
                       "/instrumentation/slip-skid-ball/indicated-slip-skid",
                       "/instrumentation/turn-indicator/indicated-turn-rate",
                       "instrumentation/vertical-speed-indicator/indicated-speed-fpm",
                       "/controls/flight/aileron",
                       "/controls/flight/elevator",
                       "/controls/flight/rudder",
                       "/controls/flight/flaps",
                       "/controls/engines/engine/throttle",
                       "/controls/engines/current-engine/throttle",
                       "/controls/switches/master-avionics",
                       "/controls/switches/starter",
                       "/engines/active-engine/auto-start",
                       "/controls/flight/speedbrake",
                       "/sim/model/c172p/brake-parking",
                       "/controls/engines/engine/primer",
                       "/controls/engines/current-engine/mixture",
                       "/controls/switches/master-bat",
                       "/controls/switches/master-alt",
                       "/engines/engine/rpm"};

    string strValue;
    int index = 0;
    for (int i = 0; i < 36; i++) {
      // check !!
      string name = names[i];
      string sim = sims[i];
      while (buffer[index] != ',' && buffer[index] != '\0') {
        strValue += buffer[index];
        index++;
      }
      index++;

      double value = stod(strValue);
      this->setNameMap(name, sim, value);
      this->setSimMap(sim, name, value);
      strValue = "";
    }
  }
  queue<string> commandsToSimulator;
  map<string, pair<string, double>> nameMap;
  map<string, pair<string, double>> simMap;
  map<string, double> varMap;
};
#endif //FLIGHTGEARPROJECT_SYMBOLTABLE_H
