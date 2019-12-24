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
#include "cstring"

using namespace std;



int OpenServerCommand::exec(vector<string> params) {

  string names[36] = {"0","1","2","3","4","5","6","7","8","9","10","11","12","13",
                      "14","15","16","17","18","19","20","21","22","23","24",
                      "25","26","27","28","29","30","31","32","33","34","35"};
//  for(int i=0 ; i<names->size() ; i++) {
//    names[i] = to_string(i);
//  }
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

  int socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if(socketfd == -1) {
    cerr << "Could not create a socket" << endl;
    return -1;
    
  }

  sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons((uint16_t)stoi(params[0]));

  if(bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
    cerr<<"Could not bind the socket to an IP"<<endl;
    return -2;
  }

  if(listen(socketfd,1) == -1) {
    cerr<<"Error during listening command"<<endl;
    return -3;
  }
  socklen_t addrlen = sizeof(sockaddr_in);
  //int addressSize = sizeof(address);
  int client_socket = accept(socketfd, (struct sockaddr *)&address, &addrlen);

  if(client_socket == -1) {
    cerr<<"Error accepting client"<<endl;
    return -4;
  }

  close(socketfd);

  //check !!
  thread thread1(&OpenServerCommand::readFromClient, this, client_socket, names, sims);
  thread1.detach();
  return this->numParams;
}

void OpenServerCommand::readFromClient(int client_socket, string names[36], string sims[36]) {
  char buffer[1024]={0};
  int valread = read(client_socket, buffer, 1024);
  while(buffer[0] != '\n') {
    cout<<buffer<<endl;
    SymbolTable &symblTbl = SymbolTable::getInstance();
    int i=0;
    string strValue;
    int index=0;
    for(int i = 0; i<36 ; i++) {
      // check !!
      string name = names[i];
      string sim = sims[i];
      while(buffer[index] != ',' && buffer[index] != '\0') {
        strValue += buffer[index];
        index++;
      }
      index++;

      double value = stod(strValue);
      symblTbl.setNameMap(name, sim, value);
      symblTbl.setSimMap(sim, name, value);
      strValue = "";
    }
    valread = read(client_socket, buffer, 1024);
  }

}

