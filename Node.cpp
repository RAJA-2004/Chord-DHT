#include "Node.h"
#include "Constant.h"
#include "Helper.h"

using namespace std;

// constructor call
Node::Node()
{
    fingerTable = vector<pair<pair<string, int>, lli>>(M + 1);
    successorList = vector<pair<pair<string, int>, lli>>(R + 1);
    isInRing = false;
}

// indicates node is not in DHT
void Node::setStatus()
{
    isInRing = false;
}

void Node::setSuccessor(string ip, int port, lli hash)
{
    for (int i = 1; i <= R; i++)
    {
        successorList[i] = make_pair(make_pair(ip, port), hash);
    }
}

void Node::setPredecessor(string ip, int port, lli hash)
{
    predecessor.first.first = ip;
    predecessor.first.second = port;
    predecessor.second = hash;
}

void Node::setId(lli Nodeid)
{
    id = Nodeid;
}

void Node::setFingerTable(string ip, int port, lli hash)
{
    for (int i = 1; i <= M; i++)
    {
        fingerTable[i] = make_pair(make_pair(ip, port), hash);
    }
}

void Node::storeKey(lli key, string val)
{
    dictionary[key] = val;
}

void Node::printKeys()
{
    map<lli, string>::iterator it;

    for (it = dictionary.begin(); it != dictionary.end(); it++)
    {
        cout << it->first << " " << it->second << endl;
    }
}

void Node::setSuccessorList(string ip, int port, lli hash)
{
    HelperFunctions help;

    vector<pair<string, int>> list = help.getSuccessorListFromNode(successor.first.first, successor.first.second);

    if (list.size() != R)
    {
        return;
    }
    successorList[1] = successor;
    for (int i = 2; i <= R; i++)
    {
        successorList[i].first.first = list[i - 2].first;
        successorList[i].first.second = list[i - 2].second;
        successorList[i].second = help.getHash(list[i - 2].first + ":" + to_string(list[i - 2].second));
    }
}

void Node::fix_fingers()
{
}
void checkPredecessor();
void checkSuccessor();
void stabilize();
void notify(pair<pair<string, int>, lli> node);

void printKeys()
{
}
vector<pair<lli, string>> getAllKeysForSuccessor();
vector<pair<lli, string>> getKeysForPredecessor(lli nodeId);

vector<pair<pair<string, int>, lli>> Node::getFingerTable()
{
    return fingerTable;
}

lli Node::getId()
{
    return id;
}

pair<pair<string, int>, lli> Node::getSuccessor()
{
    return successor;
}

pair<pair<string, int>, lli> Node::getPredecessor()
{
    return predecessor;
}

string Node::getValue(lli key)
{
    if (dictionary.find(key) != dictionary.end())
    {
        return dictionary[key];
    }
    else
        return "";
}

vector<pair<pair<string, int>, lli>> Node::getSuccessorList()
{
    return successorList;
}

bool Node::getStatus()
{
    return isInRing;
}
