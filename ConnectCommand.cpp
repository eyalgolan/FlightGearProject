//
// Created by eyal on 16/12/19.
//

#include "ConnectCommand.h"
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "string"
#include "Lock.h"

using namespace std;
int ConnectCommand::exec(vector<string> params) {
  cout<<"I'm trying to be a client"<<endl;
  int client_socket = socket(AF_INET, SOCK_STREAM, 0);
  if(client_socket == -1) {
    cerr<<"Could not create a socket"<<endl;
    return -1;
  }
  cout<<params[0].c_str()<<endl;
  cout<<params[1]<<endl;
  sockaddr_in address;
  address.sin_family = AF_INET;
  const char* ip = params[0].c_str();
  address.sin_addr.s_addr = inet_addr(ip);
  address.sin_port = htons((uint16_t)stoi(params[1]));

  int is_connect = connect(client_socket, (struct sockaddr *)&address, sizeof(address));
  if(is_connect == 0) {
    cerr<<"Could not connect to host server"<<endl;
    return -2;
  }
  else {
    cout<<"Client is now connected to server"<<endl;
  }

  return this->numParams;
}