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
//  double defaultValue = 0;
//  xmlFormat.push_back("airspeed-indicator_indicated-speed-kt", make_pair("/instrumentation/airspeed-indicator/indicated-speed-kt", defaultValue));
//  xmlFormat.push_back("time_warp", make_pair("/sim/time/warp", defaultValue));
//  xmlFormat.push_back("switches_magnetos", make_pair("/controls/switches/magnetos", defaultValue));
//  xmlFormat.push_back("heading-indicator_offset-deg", make_pair("/instrumentation/heading-indicator/offset-deg", defaultValue));
//  xmlFormat.push_back("altimeter_indicated-altitude-ft", make_pair("/instrumentation/altimeter/indicated-altitude-ft", defaultValue));
//  xmlFormat.push_back("altimeter_pressure-alt-ft", make_pair("/instrumentation/altimeter/pressure-alt-ft", defaultValue));
//  xmlFormat.push_back("attitude-indicator_indicated-pitch-deg", make_pair("/instrumentation/attitude-indicator/indicated-pitch-deg", defaultValue));
//  xmlFormat.push_back("attitude-indicator_internal-pitch-deg", make_pair("/instrumentation/attitude-indicator/internal-pitch-deg", defaultValue));
//  xmlFormat.push_back("attitude-indicator_internal-roll-deg", make_pair("/instrumentation/attitude-indicator/internal-roll-deg", defaultValue));
//  xmlFormat.push_back("attitude-indicator_internal-pitch-deg", make_pair("instrumentation/attitude-indicator/internal-pitch-deg", defaultValue));
//  xmlFormat.push_back("indicator_internal-roll-deg", make_pair("/instrumentation/attitude-indicator/internal-roll-deg", defaultValue));
//  xmlFormat.push_back("encoder_indicated-altitude-ft", make_pair("/instrumentation/encoder/indicated-altitude-ft", defaultValue));
//  xmlFormat.push_back("encoder_pressure-alt-ft", make_pair("/instrumentation/encoder/pressure-alt-ft", defaultValue));
//  xmlFormat.push_back("gps_indicated-altitude-ft", make_pair("/instrumentation/gps/indicated-altitude-ft", defaultValue));
//  xmlFormat.push_back("gps_indicated-ground-speed-kt", make_pair("/instrumentation/gps/indicated-ground-speed-kt", defaultValue));
//  xmlFormat.push_back("indicated-heading-deg", make_pair("/instrumentation/heading-indicator/indicated-heading-deg", defaultValue));
//  xmlFormat.push_back("magnetic-compass_indicated-heading-deg", make_pair("/instrumentation/magnetic-compass/indicated-heading-deg", defaultValue));
//  xmlFormat.push_back("slip-skid-ball_indicated-slip-skid", make_pair("/instrumentation/slip-skid-ball/indicated-slip-skid", defaultValue));
//  xmlFormat.push_back("turn-indicator_indicated-turn-rate", make_pair("/instrumentation/turn-indicator/indicated-turn-rate", defaultValue));
//  xmlFormat.push_back("vertical-speed-indicator_indicated-speed-fpm", make_pair("instrumentation/vertical-speed-indicator/indicated-speed-fpm", defaultValue));
//  xmlFormat.push_back("flight_aileron", make_pair("/controls/flight/aileron", defaultValue));
//  xmlFormat.push_back("flight_elevator", make_pair("/controls/flight/elevator", defaultValue));
//  xmlFormat.push_back("flight_rudder", make_pair("/controls/flight/rudder", defaultValue));
//  xmlFormat.push_back("flight_flaps", make_pair("/controls/flight/flaps", defaultValue));
//  xmlFormat.push_back("engine_throttle", make_pair("/controls/engines/engine/throttle", defaultValue));
//  xmlFormat.push_back("current-engine_throttle", make_pair("/controls/engines/current-engine/throttle", defaultValue));
//  xmlFormat.push_back("switches_master-avionics", make_pair("/controls/switches/master-avionics", defaultValue));
//  xmlFormat.push_back("switches_starter", make_pair("/controls/switches/starter", defaultValue));
//  xmlFormat.push_back("active-engine_auto-start", make_pair("/engines/active-engine/auto-start", defaultValue));
//  xmlFormat.push_back("flight_speedbrake", make_pair("/controls/flight/speedbrake", defaultValue));
//  xmlFormat.push_back("c172p_brake-parking", make_pair("/sim/model/c172p/brake-parking", defaultValue));
//  xmlFormat.push_back("engine_primer", make_pair("/controls/engines/engine/primer", defaultValue));
//  xmlFormat.push_back("current-engine_mixture", make_pair("/controls/engines/current-engine/mixture", defaultValue));
//  xmlFormat.push_back("switches_master-bat", make_pair("/controls/switches/master-bat", defaultValue));
//  xmlFormat.push_back("switches_master-alt", make_pair("/controls/switches/master-alt", defaultValue));
//  xmlFormat.push_back("engine_rpm", make_pair("/engines/engine/rpm", defaultValue));

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
  int i=0;
  for(itr = xmlFormat.begin(); itr != xmlFormat.end(); itr++) {
    // check !!
    string name = itr.first;
    string sim = itr.second.first;
    double value = buffer[i];
    symblTbl.setNameMap(name, sim, value);
    symblTbl.setSimMap(sim, name, value);
    i+=2;
  }

  std::cout<<buffer<<std::endl;

}