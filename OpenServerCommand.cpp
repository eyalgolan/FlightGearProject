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
#include "Parser.h"
#include "chrono"

using namespace std;

/**
 * Function: exec
 * Opens a thread that runs a server.
 * The server thread reads the data sent from the simulator
 * @param params: recieves the server port
 * @return how much to advance in the input vector
 */
int OpenServerCommand::exec(vector<string> params) {

  /*
   * server setup
   */

  //opening a socket
  int socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd == -1) {
    cerr << "Could not create a socket" << endl;
    return -1;

  }

  sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons((uint16_t) stoi(params[0]));

  //binding the socket to the requested address
  if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
    cerr << address.sin_addr.s_addr << endl;
    cerr << address.sin_port << endl;
    cerr << "Could not bind the socket to an IP" << endl;
    return -2;
  }

  //waiting for the simulator to approach the server to make a connection
  if (listen(socketfd, 1) == -1) {
    cerr << "Error during listening command" << endl;
    return -3;
  }

  //accepting a client
  socklen_t addrlen = sizeof(sockaddr_in);
  int client_socket = accept(socketfd, (struct sockaddr *) &address, &addrlen);

  if (client_socket == -1) {
    cerr << "Error accepting client" << endl;
    return -4;
  } else {
    cout << "Simulator connected to server" << endl;
  }
  //closing the listening socket
  close(socketfd);

  //opening a detached thread that receives data from the simulator
  thread thread1(&OpenServerCommand::readFromClient, this, client_socket);
  thread1.detach();
  return this->numParams;
}

/**
 * Function: readFromClient
 * reading received data from the simulator line-by-line and updating the
 * symbol table accordingly
 * @param client_socket
 */
void OpenServerCommand::readFromClient(int client_socket) {
  //hard coded sim values from generic_small.xml
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

  char buffer[1024] = {0};
  ssize_t valread = read(client_socket, buffer, 1024);
  SymbolTable &symblTbl = SymbolTable::getInstance();

  //reading received data from the simulator line-by-line
  while (buffer[0] != '\n') {
    string strValue;
    int index = 0;

    //getting each of the values received in the current line
    for (int i = 0; i < 36; i++) {
      string sim;
      sim = sims[i];
      while (buffer[index] != ',' && buffer[index] != '\0') {
        strValue += buffer[index];
        index++;
      }
      index++;

      //updating the symbol table with the received data
      double value = stod(strValue);
      symblTbl.updateTable("", sim, value, "server");
      strValue = "";
    }
    valread = read(client_socket, buffer, 1024);
  }
}

