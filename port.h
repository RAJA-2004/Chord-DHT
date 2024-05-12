#ifndef port_h
#define port_h

#include "HeaderFile.h"

class SocketAndPort
{
private:
	int portNoServer;
	int sockNumber;
	struct sockaddr_in current; // contains sin_family, sin_addr, sin_port and sin_zero

public:
	void specifyPortServer();
	void changePortNumber(int portNo);
	void closeSocket();
	bool portInUse(int portNo);
	string getIpAddress();
	int getPortNumber();
	int getSocketFd();
};

#endif