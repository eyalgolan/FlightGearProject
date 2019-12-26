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
  void update(string name, string sim, double value, string calledFrom);
  SymbolTable(SymbolTable const&) = delete;
  void operator=(SymbolTable const&) = delete;
 private:
  void updateFromServer(string name, string sim, double value);
  void updateFromVar(string name, string sim, double value);
  SymbolTable() {
    string buffer =
        "1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36";
    string names[36] =
        {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12",
         "13",
         "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24",
         "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35"};

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
  map<string, pair<string, double>> nameMap;
  map<string, pair<string, double>> simMap;

};
#endif //FLIGHTGEARPROJECT_SYMBOLTABLE_H
