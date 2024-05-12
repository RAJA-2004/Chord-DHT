#include "HeaderFile.h"
#include <iostream>
#include <winsock2.h>
#include <winsock.h>
#include "port.h"

using namespace std;

void SocketAndPort::specifyPortServer(){

    /*Generate a random function between 1024 and 65535(i.e. 2^16 -1 )*/
    srand(time(0));
    portNoServer = rand() % 655356;

    if(portNoServer < 1024)
        portNoServer+=1024;
    
    if(portInUse(portNoServer)){
        specifyPortServer();
    }

    socklen_t l = sizeof(current);

    sockNumber = socket(AF_INET,SOCK_DGRAM,0);             //socket(Domain address(of IPv4),supports datagrams,0(default family))

    current.sin_family = AF_INET;
	current.sin_port = htons(portNoServer);                 //converts port to desirable datasize
	current.sin_addr.s_addr = inet_addr("127.0.0.1");       //default address when nothing is given after Port

    /*bind -- server side while connect() -- client side*/
	if( bind(sockNumber,(struct sockaddr *)&current,l) < 0){
		perror("Local IP Address and Port not assigned.");
		exit(-1);
	}
    else{
        string ip = inet_ntoa(current.sin_addr);
        int port = current.sin_port;
        cout<<"You've been assigned default port number: "<<port<<" and ip address: "<<ip<<endl;
        cout<<"To assign Port of your choice, enter port command with port"<<endl;
    }

}

/* change Port Number */
void SocketAndPort::changePortNumber(int newPortNumber){
	if(newPortNumber < 1024 || newPortNumber > 65535){
		cout<<"Please enter a valid port number\n";
	}
	else{
		if( portInUse(newPortNumber) ){
			cout<<"Sorry but port number is already in use\n";
		}
		else{
			close(sockNumber);
			socklen_t len = sizeof(current);
			sockNumber = socket(AF_INET,SOCK_DGRAM,0); 
			current.sin_port = htons(newPortNumber);
			if( bind(sockNumber,(struct sockaddr *)&current,len) < 0){
				perror("error");
				current.sin_port = htons(portNoServer);
			}
			else{
				portNoServer = newPortNumber;
				cout<<"Port number changed to : "<<portNoServer<<endl;
			}
		}
	}
}

/*Check if a Port Number is already in use*/
bool SocketAndPort::portInUse(int portNo){
    int newSockNumber = socket(AF_INET,SOCK_DGRAM,0);
    
    /*create a new socket using this and see if it's already bound*/
    struct sockaddr_in newSocket;
    socklen_t len = sizeof(newSocket);
    newSocket.sin_family = AF_INET;
    newSocket.sin_port = htons(portNo);
    newSocket.sin_addr.s_addr = inet_addr("127.0.0.1");

    if( bind(newSockNumber,(struct sockaddr *)&newSocket,len) < 0){
		return true;
	}
	else{
		close(newSockNumber);
		return false;
	}
}

/*function to get IP address*/
string SocketAndPort::getIpAddress(){
    string ip = inet_ntoa(current.sin_addr);                        //convert to human recognizable address(dot format)
    return ip;
}

/*function to get Port Number*/
int SocketAndPort::getPortNumber(){
    return portNoServer;
}

/*get Socket File Descriptor*/
int SocketAndPort::getSocketFd(){
	return sockNumber;
}

/* close socket */
void SocketAndPort::closeSocket(){
	close(sockNumber);
}

int main(){
    SocketAndPort sp = SocketAndPort();
    sp.specifyPortServer();
}
