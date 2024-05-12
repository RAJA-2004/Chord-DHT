#include "Helper.h"
#include "Node.h"
#include "port.h"

/*splits the command entered by user for inference*/
vector<string> HelperFunctions::splitCommand(string command)
{
    vector<string> instructions;
    int pos = 0;
    do
    {
        pos = command.find(' ');
        string arg = command.substr(0, pos);
        instructions.push_back(arg);
        command = command.substr(pos + 1);
    } while (pos != -1);
    return instructions;
}

/*split the key of node into ip and port. Originally, key is ip:port.*/
pair<string, int> HelperFunctions::getIpAndPort(string key)
{
    int pos;
    string ip, port;
    pos = key.find(':');

    if (pos == -1)
    {
        cout << "< Key of node not in correct format";
        return;
    }
    pair<string, int> Ip_and_port;
    ip = key.substr(0, pos);
    port = key.substr(pos + 1);

    Ip_and_port.first = ip;
    Ip_and_port.second = atoi(port.c_str()); // atoi() : convert string to integer; c_str is required as atoi takes only c-type strings, ending with null

    return Ip_and_port;
}

/* key will be in form of key:value , will seperate key and value and return it */
pair<lli, string> HelperFunctions::getKeyAndVal(string keyAndVal)
{

    int pos = keyAndVal.find(':');
    string key = keyAndVal.substr(0, pos);
    string val = keyAndVal.substr(pos + 1);

    pair<lli, string> keyAndValPair;
    keyAndValPair.first = stoll(key);
    keyAndValPair.second = val;

    return keyAndValPair;
}

/* will decide if id is in form of key:value or not */
bool HelperFunctions::isKeyValue(string id)
{

    int pos = id.find(":");

    if (pos == -1)
        return false;

    for (int i = 0; i < pos; i++)
    {
        if (!(id[i] >= 48 && id[i] <= 57))
            return false;
    }

    return true;
}

/* set details of server to which you want to connect to */
void HelperFunctions::setServerDetails(struct sockaddr_in &server, string ip, int port)
{
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(ip.c_str());
    server.sin_port = htons(port);
}

/* combine ip and port as ip:port and return string for hashing function */
string HelperFunctions::combineIpAndPort(string ip, string port)
{
    string ipAndPort = "";
    int i = 0;

    for (i = 0; i < ip.size(); i++)
    {
        ipAndPort += ip[i];
    }

    ipAndPort += ':';

    for (i = 0; i < port.size(); i++)
    {
        ipAndPort += port[i];
    }

    return ipAndPort;
}