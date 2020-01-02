//
// Created by eyal on 19/12/19.
//

#ifndef FLIGHTGEARPROJECT_SYMBOLTABLE_H
#define FLIGHTGEARPROJECT_SYMBOLTABLE_H

#import "map"
#import "string"
#import "Parser.h"
#import "mutex"
#import "queue"
#import "string"

using namespace std;


class SymbolTable {
 public:
  mutex g_updateLock;
  static SymbolTable& getInstance() {
    static SymbolTable instance;
    return instance;
  }
  string getSetExp() {
    string toSet;
    for(auto it = this->nameMap.begin(); it != this->nameMap.end() ; it++) {
      toSet += it->first + "=" + to_string(it->second.second) + ";";
    }
    for(auto varIt = this->varMap.begin(); varIt != this->varMap.end() ; varIt++) {
      toSet += varIt->first + "=" + to_string(varIt->second) + ";";
    }
    return toSet;
  }
  bool isInNameMap (string name) {
//      if(this->nameMap.find(name) != this->nameMap.end()) {
//        cout << "name is " + name + " and result of search is true";
//      }
//      else {
//        cout << "name is " + name + " and result of search is false";
//      }
    if(this->nameMap.find(name) != this->nameMap.end()) {
      return true;
    }
    return false;
  }

  bool isInVarMap (string name) {
//      if(this->nameMap.find(name) != this->nameMap.end()) {
//        cout << "name is " + name + " and result of search is true";
//      }
//      else {
//        cout << "name is " + name + " and result of search is false";
//      }
    if(this->varMap.find(name) != this->varMap.end()) {
      return true;
    }
    return false;
  }

  void addToVarMap (string name, double value) {
    this->varMap.insert(make_pair(name, value));
  }
  bool isInSimMap (string sim) {
    if(this->simMap.find(sim) != this->simMap.end()) {
      return true;
    }
    return false;
  }

  map<string, pair<string, double>> getNameMap() {
    return this->nameMap;
  }
  map<string, pair<string, double>> getSimMap() {
    return this->simMap;
  }
  map<string, double> getVarMap() {
    return this->varMap;
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
  SymbolTable(SymbolTable const&) = delete;
  void operator=(SymbolTable const&) = delete;
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
