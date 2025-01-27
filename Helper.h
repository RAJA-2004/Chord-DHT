#ifndef helper_h
#define helper_h

#include <iostream>

#include "Node.h"

using namespace std;

typedef long long int lli;

class HelperFunctions
{

public:
	vector<string> splitCommand(string command);
	string combineIpAndPort(string ip, string port);
	vector<pair<lli, string>> seperateKeysAndValues(string keysAndValues);
	vector<pair<string, int>> seperateSuccessorList(string succList);
	string splitSuccessorList(vector<pair<pair<string, int>, lli>> list);

	lli getHash(string key);
	pair<string, int> getIpAndPort(string key);

	bool isKeyValue(string id);

	bool isNodeAlive(string ip, int port);

	void setServerDetails(struct sockaddr_in &server, string ip, int port);
	void setTimer(struct timeval &timer);

	void sendNeccessaryKeys(Node &nodeInfo, int newSock, struct sockaddr_in client, string nodeIdString);
	void sendKeyToNode(pair<pair<string, int>, lli> node, lli keyHash, string value);
	void sendValToNode(Node nodeInfo, int newSock, struct sockaddr_in client, string nodeIdString);
	string getKeyFromNode(pair<pair<string, int>, lli> node, string keyHash);
	pair<lli, string> getKeyAndVal(string keyAndVal);
	void getKeysFromSuccessor(Node &nodeInfo, string ip, int port);
	void storeAllKeys(Node &nodeInfo, string keysAndValues);

	pair<pair<string, int>, lli> getPredecessorNode(string ip, int port, string ipClient, int ipPort, bool forStabilize);
	lli getSuccessorId(string ip, int port);

	void sendPredecessor(Node nodeInfo, int newSock, struct sockaddr_in client);
	void sendSuccessor(Node nodeInfo, string nodeIdString, int newSock, struct sockaddr_in client);
	void sendSuccessorId(Node nodeInfo, int newSock, struct sockaddr_in client);
	void sendAcknowledgement(int newSock, struct sockaddr_in client);

	vector<pair<string, int>> getSuccessorListFromNode(string ip, int port);
	void sendSuccessorList(Node &nodeInfo, int sock, struct sockaddr_in client);
};

#endif