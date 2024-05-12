#include <iostream>
#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <vector>
#include <cstdlib>
#include <sys/types.h>
#include <thread>
#include <ctime>
#include <cmath>
#include <mutex>

#ifdef _WIN32 // Check if compiling for Windows

#include <winsock2.h>
#include <ws2tcpip.h>
// #include <openssl/sha.h>
#pragma comment(lib, "libcrypto.lib")
#pragma comment(lib, "ws2_32.lib")

#else // Assume Unix-like system

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <openssl/sha.h>

#endif

using namespace std;