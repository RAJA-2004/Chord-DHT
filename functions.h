#ifndef functions_h
#define functions_h

#include <iostream>

#include "port.h"
#include "Node.h"

using namespace std;

typedef long long int lli;

void put(string key, string value, Node &nodeInfo);
void get(string key, Node nodeInfo);
void create(Node &nodeInfo);
void join(Node &nodeInfo, string ip, string port);
void printState(Node nodeInfo);
void listenTo(Node &nodeInfo);
void doStabilize(Node &nodeInfo);
void callNotify(Node &nodeInfo, string ipAndPort);
void callFixFingers(Node &nodeInfo);
void doTask(Node &nodeInfo, int newSock, struct sockaddr_in client, string nodeIdString);
void leave(Node &nodeInfo);
#endif