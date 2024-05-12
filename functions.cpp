#include "Node.h"
#include "Helper.h"
#include "Constant.h"
#include "functions.h"
#include "HeaderFile.h"
#include "mingw.thread.h"

typedef long long int lli;

using namespace std;

HelperFunctions help = HelperFunctions();

/* create a new ring */
void create(Node &nodeInfo)
{

    string ip = nodeInfo.sp.getIpAddress();
    int port = nodeInfo.sp.getPortNumber();

    /* key to be hashed for a node is ip:port */
    string key = ip + ":" + to_string(port);

    lli hash = help.getHash(key);

    /* setting id, successor , successor list , predecessor ,finger table and status of node */
    nodeInfo.setId(hash);
    nodeInfo.setSuccessor(ip, port, hash);
    nodeInfo.setSuccessorList(ip, port, hash);
    nodeInfo.setPredecessor("", -1, -1);
    nodeInfo.setFingerTable(ip, port, hash);
    nodeInfo.setStatus();

    /* launch threads,one thread will listen to request from other nodes,one will do stabilization */
    std::thread second(listenTo, ref(nodeInfo));
    second.detach();

    std::thread fifth(doStabilize, ref(nodeInfo));
    fifth.detach();

} // End of create function

/* listen to any contacting node */
void listenTo(Node &nodeInfo)
{
    struct sockaddr_in client;
    socklen_t l = sizeof(client);

    /* wait for any client to connect and create a new thread as soon as one connects */
    while (1)
    {
        char charNodeId[40];
        int sock = nodeInfo.sp.getSocketFd();
        int len = recvfrom(sock, charNodeId, 1024, 0, (struct sockaddr *)&client, &l);
        charNodeId[len] = '\0';
        string nodeIdString = charNodeId;

        /* launch a thread that will perform diff tasks acc to received msg */
        thread f(doTask, ref(nodeInfo), sock, client, nodeIdString);
        f.detach();
    }
}

void doStabilize(Node &nodeInfo)
{

    /* do stabilize tasks */
    while (1)
    {

        nodeInfo.checkPredecessor();

        nodeInfo.checkSuccessor();

        nodeInfo.stabilize();

        nodeInfo.updateSuccessorList();

        nodeInfo.fix_fingers();

        this_thread::sleep_for(chrono::milliseconds(300));
    }
}

/* call notify of current node which will notify curr node of contacting node */
void callNotify(Node &nodeInfo, string ipAndPort)
{

    ipAndPort.pop_back();
    ipAndPort.pop_back();

    /* get ip and port of client node */
    pair<string, int> ipAndPortPair = help.getIpAndPort(ipAndPort);
    string ip = ipAndPortPair.first;
    int port = ipAndPortPair.second;
    lli hash = help.getHash(ipAndPort);

    pair<pair<string, int>, lli> node;
    node.first.first = ip;
    node.first.second = port;
    node.second = hash;

    /* notify current node about this node */
    nodeInfo.notify(node);
}
