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
#include "thread"
#include "SymbolTable.h"
/**
 * Function name : ConnectCommand
 * Opens a thread that runs a client .
 * The client thread send the data to the server.
 * @param params: recieves the server port an the ip
 * @return how much to advance in the input vector
 */
using namespace std;
int ConnectCommand::exec(vector<string> params) {
  //client socket
  int client_socket = socket(AF_INET, SOCK_STREAM, 0);
  // returning -1 if we Could not create a socket
  if (client_socket == -1) {
    cout << "Could not create a socket" << endl;
    return -1;
  }
  // we need create sockaddr obj to hold address of the server
  sockaddr_in address;
  int length = params[0].size();
  char ip[length + 1];
  strcpy(ip, params[0].c_str());
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = inet_addr(ip);// the localhost address
  address.sin_port = htons(stoi(params[1]));
  // requesting a connection
  int is_connect =
      connect(client_socket, (struct sockaddr *) &address, sizeof(address));
  // if "Could not connect to host server
  if (is_connect == -1) {
    cerr << "Could not connect to host server" << endl;
    return -2;
  } else {
    cout << "client is now connect to simulator" << endl;
    // if we connect - run the thread
    thread thread2(&ConnectCommand::writeToClient, this, client_socket);
    thread2.detach();
  }
// how much to advance in the input vector
  return this->numParams;
}
// the func that give as the ability read from the queue
string ConnectCommand::readFromQueue() {

  SymbolTable &symblTbl = SymbolTable::getInstance();
  string update = symblTbl.getFirstInQueue();
  symblTbl.popFromQueue();

  return update;
}
/** the writing to client
 * we update the server from the client that hold a queue commands
 *
 * @param client_socket
 */
void ConnectCommand::writeToClient(int client_socket) {
  SymbolTable &symblTbl = SymbolTable::getInstance();
  string update;
  while (true) {
    symblTbl.g_updateLock.lock();
    bool queueState = !symblTbl.isQueueEmpty();
    symblTbl.g_updateLock.unlock();
    /*
     * while the queue is not empty we need send all the data command to the
     * simulator
     */
    while (queueState) {
      symblTbl.g_updateLock.lock();
      update = this->readFromQueue();
      int is_sent =
          send(client_socket,
               update.c_str(),
               strlen(update.c_str()),
               0); //the sending
      queueState = !symblTbl.isQueueEmpty();
      symblTbl.g_updateLock.unlock();

    }
  }
}
