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
#include "SymbolTable.h"

using namespace std;
int ConnectCommand::exec(vector<string> params) {

  int client_socket = socket(AF_INET, SOCK_STREAM, 0);
  if(client_socket == -1) {
    cout<<"Could not create a socket"<<endl;
    return -1;
  }
  sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = inet_addr("127.0.0.1");
  address.sin_port = htons(5402);

  int is_connect = connect(client_socket, (struct sockaddr *)&address, sizeof(address));

  if(is_connect == -1) {
    cerr<<"Could not connect to host server"<<endl;
    return -2;
  }
//  else {
//    cout<<"Client is now connected to server"<<endl;
//  }
//  const char* ip = params[0].c_str();
//
//  address.sin_addr.s_addr = inet_addr(ip);
//  address.sin_port = htons((uint16_t)stoi(params[1]));
//
//
//  int is_connect = connect(client_socket, (struct sockaddr *)&address, sizeof(address));

//  if(is_connect == -1) {
//    cerr<<address.sin_addr.s_addr<<endl;
//    cerr<<address.sin_port<<endl;
//    cerr<<"Could not connect to host server"<<endl;
//    //return -2;
//  }
  else {
    cout<< is_connect <<endl;
    cout<<"Client is now connected to server"<<endl;
    thread thread2(&ConnectCommand::writeToClient, this, client_socket);
    thread2.detach();
  }

  return this->numParams;
}

string ConnectCommand::readFromQueue() {
  cout<<"trying to read from queue"<<endl;
  SymbolTable &symblTbl = SymbolTable::getInstance();
  symblTbl.g_updateLock.lock();
  string update = symblTbl.getQueue().front();
  symblTbl.getQueue().pop();
  symblTbl.g_updateLock.unlock();
  cout<<"success reading from queue"<<endl;
  return update;
}
void ConnectCommand::writeToClient(int client_socket) {
  cout<<"i am in writing clientet before whiles"<<endl;
  SymbolTable &symblTbl = SymbolTable::getInstance();
  while (true) {
      symblTbl.g_updateLock.lock();
    bool queueState = !symblTbl.getQueue().empty();
    symblTbl.g_updateLock.unlock();
    while (queueState) {
      cout << "trying to write to client" << endl;
      string update = this->readFromQueue();
      cout << "trying to write to client also queue no empty " << endl;
      cout << update.c_str() << endl;
      cout << client_socket << endl;
      int is_sent =
          send(client_socket, update.c_str(), strlen(update.c_str()), 0);
      cout << update.c_str() << endl;
      if (is_sent == -1) {
        cout << update.c_str() << endl;
        cout << "Error sending message" << endl;
      } else {
        cout << "message send to simulator" << endl;
      }
      cout << "success writing to client" << endl;
      symblTbl.g_updateLock.lock();
      queueState = !symblTbl.getQueue().empty();
      symblTbl.g_updateLock.unlock();
    }
  }
}

//void ConnectCommand::updateSimulator() {
//
//}