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

using namespace std;

int OpenServerCommand::exec(vector<string> params) {

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

  int client_socker = accept(socketfd, (struct sockaddr *)&address,
                           (socklen_t*)&address);

  if(client_socker == -1) {
    cerr<<"Error accepting client"<<endl;
    return -4;
  }
  return this->numParams;
}