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
#include "thread"

using namespace std;

/*
 * SymbolTable: A singleton class responsible for saving the state of the plane
 */
class SymbolTable {
 public:

  // Global data member
  mutex g_updateLock;

  //Public functions

  /**
   * Function: getInstance
   * Returns the singleton instance of the SymbolTable class
   */
  static SymbolTable &getInstance() {
    static SymbolTable instance;
    return instance;
  }

  string getSetExp();
  bool isInNameMap(string);
  bool isInSimMap(string);
  bool isInVarMap(string);
  void addToVarMap(string name, double value);
  string getNameMapSim(string);
  double getNameMapValue(string);
  double getVarMapValue(string);
  bool isQueueEmpty();
  string getFirstInQueue();
  void pushToQueue(string command);
  void popFromQueue();
  void insertToNameMap(string name, string sim, double value);
  void insertToSimMap(string sim, string name, double value);
  void updateTable(string name, string sim, double value, string calledFrom);
  SymbolTable(SymbolTable const &) = delete;
  void operator=(SymbolTable const &) = delete;

 private:

  // Private data members
  queue<string> commandsToSimulator;
  map<string, pair<string, double>> nameMap;
  map<string, pair<string, double>> simMap;
  map<string, double> varMap;

  // Private functions
  void updateFromServer(string name, string sim, double value);
  void updateFromDefineVar(string name, string sim, double value);
  void updateFromSetVar(string name, string sim, double value);

  /**
   * SymbolTable constructor, creating the symbolTable with default names and
   * values. sims are from the generic_small.xml.
   */
  SymbolTable() {

    /*
     * creating the symbolTable with default names and values.
     * sims are from the generic_small.xml
     */
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

    //build the name and sim maps
    for (int i = 0; i < 36; i++) {

      string name = names[i];
      string sim = sims[i];

      //go over buffer and get values
      while (buffer[index] != ',' && buffer[index] != '\0') {
        strValue += buffer[index];
        index++;
      }
      index++;

      //populate name and sim maps
      double value = stod(strValue);
      this->insertToNameMap(name, sim, value);
      this->insertToSimMap(sim, name, value);
      strValue = "";
    }
  }
};
#endif //FLIGHTGEARPROJECT_SYMBOLTABLE_H
