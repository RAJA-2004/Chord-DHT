#ifndef Node_h
#define Node_h

#include <map>
#include "HeaderFile.h"
#include "port.h"

typedef long long int lli;

class Node
{
private:
        lli id;

        // stores (ip, port, hashValue)
        pair<pair<string, int>, lli> predecessor;
        pair<pair<string, int>, lli> successor;

        // used for routing messages and performing key lookups
        // each node corresponds to successor node in DHT
        // indexed with hashValues
        vector<pair<pair<string, int>, lli>> fingerTable;

        // stores the hashValue and ip pair
        map<lli, string> dictionary;

        // allows redundancy and fault tolerance
        // If a node's immediate successor fails or leaves the network, the node can quickly switch to its next available successor from the list without disrupting the system's functionality.
        // not defined predecessorList bcz Chord primarily focuses on forward-pointing routing
        vector<pair<pair<string, int>, lli>> successorList;

        // indicates whether node is part of DHT or not
        bool isInRing;

public:
        SocketAndPort sp;

        pair<pair<string, int>, lli> findSuccessor(lli nodeId);
        pair<pair<string, int>, lli> closestPrecedingNode(lli nodeId);
        void fix_fingers();
        void checkPredecessor();
        void checkSuccessor();
        void stabilize();
        void notify(pair<pair<string, int>, lli> node);

        void printKeys();
        vector<pair<lli, string>> getAllKeysForSuccessor();
        vector<pair<lli, string>> getKeysForPredecessor(lli nodeId);
        void updateSuccessorList();

        // setters

        void setSuccessor(string ip, int port, lli hash);
        void setSuccessorList(string ip, int port, lli hash);
        void setPredecessor(string ip, int port, lli hash);
        void setFingerTable(string ip, int port, lli hash);
        void setId(lli id);
        void setStatus();
        void storeKey(lli key, string val);

        // getters

        lli getId();
        string getValue(lli key);
        vector<pair<pair<string, int>, lli>> getFingerTable();
        pair<pair<string, int>, lli> getSuccessor();
        pair<pair<string, int>, lli> getPredecessor();
        vector<pair<pair<string, int>, lli>> getSuccessorList();
        bool getStatus();
};

#endif