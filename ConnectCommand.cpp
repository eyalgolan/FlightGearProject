//
// Created by eyal on 16/12/19.
//

#include "ConnectCommand.h"
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include "string"
#include "Lock.h"
#include "thread"

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
    thread thread2(&ConnectCommand::writeToClient, this, client_socket);
    thread2.detach();
  }

  return this->numParams;
}

void ConnectCommand::writeToQueue(string update) {
  this->sendQueue.push(update);
}
string ConnectCommand::readFromQueue() {
  string update = this->sendQueue.front();
  this->sendQueue.pop();
  return update;
}
void ConnectCommand::writeToClient(int client_socket) {
  string update = this->readFromQueue();
  int is_sent = send(client_socket, update.c_str(), strlen(update.c_str()), 0);
  if(is_sent == -1) {
    cout<<update.c_str()<<endl;
    cout<<"Error sending message"<<endl;
  }
  else {
    cout<<"message send to simulator"<<endl;
  }
}

//void ConnectCommand::updateSimulator() {
//
//}