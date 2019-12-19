//
// Created by eyal on 16/12/19.
//

#include "OpenServerCommand.h"
#include <thread>
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include "SymbolTable.h"

using namespace std;



int OpenServerCommand::exec(vector<string> params) {

  vector<string, pair<string, double>> xmlFormat;
  xmlFormat.insert("airspeed-indicator_indicated-speed-kt", make_pair("/instrumentation/airspeed-indicator/indicated-speed-kt", 0));
  xmlFormat.insert("time_warp", make_pair("/sim/time/warp", 0));
  xmlFormat.insert("switches_magnetos", make_pair("/controls/switches/magnetos", 0));
  xmlFormat.insert("heading-indicator_offset-deg", make_pair("/instrumentation/heading-indicator/offset-deg", 0));
  xmlFormat.insert("altimeter_indicated-altitude-ft", make_pair("/instrumentation/altimeter/indicated-altitude-ft", 0));
  xmlFormat.insert("altimeter_pressure-alt-ft", make_pair("/instrumentation/altimeter/pressure-alt-ft", 0));
  xmlFormat.insert("attitude-indicator_indicated-pitch-deg", make_pair("/instrumentation/attitude-indicator/indicated-pitch-deg", 0));
  xmlFormat.insert("attitude-indicator_internal-pitch-deg", make_pair("/instrumentation/attitude-indicator/internal-pitch-deg", 0));
  xmlFormat.insert("attitude-indicator_internal-roll-deg", make_pair("/instrumentation/attitude-indicator/internal-roll-deg", 0));
  xmlFormat.insert("attitude-indicator_internal-pitch-deg", make_pair("instrumentation/attitude-indicator/internal-pitch-deg", 0));
  xmlFormat.insert("indicator_internal-roll-deg", make_pair("/instrumentation/attitude-indicator/internal-roll-deg", 0));
  xmlFormat.insert("encoder_indicated-altitude-ft", make_pair("/instrumentation/encoder/indicated-altitude-ft", 0));
  xmlFormat.insert("encoder_pressure-alt-ft", make_pair("/instrumentation/encoder/pressure-alt-ft", 0));
  xmlFormat.insert("gps_indicated-altitude-ft", make_pair("/instrumentation/gps/indicated-altitude-ft", 0));
  xmlFormat.insert("gps_indicated-ground-speed-kt", make_pair("/instrumentation/gps/indicated-ground-speed-kt", 0));
  xmlFormat.insert("indicated-heading-deg", make_pair("/instrumentation/heading-indicator/indicated-heading-deg", 0));
  xmlFormat.insert("magnetic-compass_indicated-heading-deg", make_pair("/instrumentation/magnetic-compass/indicated-heading-deg", 0));
  xmlFormat.insert("slip-skid-ball_indicated-slip-skid", make_pair("/instrumentation/slip-skid-ball/indicated-slip-skid", 0));
  xmlFormat.insert("turn-indicator_indicated-turn-rate", make_pair("/instrumentation/turn-indicator/indicated-turn-rate", 0));
  xmlFormat.insert("vertical-speed-indicator_indicated-speed-fpm", make_pair("instrumentation/vertical-speed-indicator/indicated-speed-fpm", 0));
  xmlFormat.insert("flight_aileron", make_pair("/controls/flight/aileron", 0));
  xmlFormat.insert("flight_elevator", make_pair("/controls/flight/elevator", 0));
  xmlFormat.insert("flight_rudder", make_pair("/controls/flight/rudder", 0));
  xmlFormat.insert("flight_flaps", make_pair("/controls/flight/flaps", 0));
  xmlFormat.insert("engine_throttle", make_pair("/controls/engines/engine/throttle", 0));
  xmlFormat.insert("current-engine_throttle", make_pair("/controls/engines/current-engine/throttle", 0));
  xmlFormat.insert("switches_master-avionics", make_pair("/controls/switches/master-avionics", 0));
  xmlFormat.insert("switches_starter", make_pair("/controls/switches/starter", 0));
  xmlFormat.insert("active-engine_auto-start", make_pair("/engines/active-engine/auto-start", 0));
  xmlFormat.insert("flight_speedbrake", make_pair("/controls/flight/speedbrake", 0));
  xmlFormat.insert("c172p_brake-parking", make_pair("/sim/model/c172p/brake-parking", 0));
  xmlFormat.insert("engine_primer", make_pair("/controls/engines/engine/primer", 0));
  xmlFormat.insert("current-engine_mixture", make_pair("/controls/engines/current-engine/mixture", 0));
  xmlFormat.insert("switches_master-bat", make_pair("/controls/switches/master-bat", 0));
  xmlFormat.insert("switches_master-alt", make_pair("/controls/switches/master-alt", 0));
  xmlFormat.insert("engine_rpm", make_pair("/engines/engine/rpm", 0));

  int socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if(socketfd == -1) {
    cerr << "Could not create a socket" << endl;
    return -1;
  }

  sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons((uint16_t)stoi(params[1]));

  if(bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
    cerr<<"Could not bind the sockert to an IP"<<endl;
    return -2;
  }

  if(listen(socketfd, 2) == -1) {
    cerr<<"Error during listening command"<<endl;
    return -3;
  }
  int addressSize = sizeof(address);
  int client_socket = accept(socketfd, (struct sockaddr *)&address,
                           (socklen_t*)&addressSize);

  if(client_socket == -1) {
    cerr<<"Error accepting client"<<endl;
    return -4;
  }

  //check !!
  thread thread1(&OpenServerCommand::readFromClient, this, client_socket, xmlFormat);
  return this->numParams;
}

void OpenServerCommand::readFromClient(int client_socket, vector<string, pair<string, double>> xmlFormat) {
  char buffer[1024]={0};
  int valread = read(client_socket, buffer, 1024);
  SymbolTable &symblTbl = SymbolTable::getInstance();
  vector<string, pair<string, double>>::iterator itr;
  for(itr = xmlFormat.begin(); itr != xmlFormat.end(); itr++) {
    // check !!
    string name = itr.first;
    string sim = itr.second.first;
    double value = itr.second.second;
    symblTbl.setNameMap(name, sim, value);
    symblTbl.setSimMap(sim, name, value);
  }

  std::cout<<buffer<<std::endl;

}