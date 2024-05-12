#include "HeaderFile.h"
#include "port.h"
#include "Helper.h"
#include "Node.h"
#include "functions.h"
#include "mingw.thread.h"

void functionMenu()
{
	/* tell about all commands */
	cout << "1) create : will create a DHT ring\n\n"
		 << endl;
	cout << "2) port <number> : will change port number to mentioned number if that port is free\n\n"
		 << endl;
	cout << "3)join <ip> <port> : will join ring by connecting to main node having ip and port\n\n"
		 << endl;
	cout << "4) put <key> <value> : will put key and value to the node it belongs to\n\n"
		 << endl;
	cout << "5) get <key> : will get value of mentioned key\n\n"
		 << endl;
	cout << "6) printstate : will print successor, predecessor, fingerTable and Successor list\n\n"
		 << endl;
}
int main()
{
	Node nodeInfo = Node();
	SocketAndPort sp = SocketAndPort();
	sp.specifyPortServer();
	string command;
	functionMenu();

	while (1)
	{
		cout << "> ";
		getline(cin, command);

		/*Split the commands into words*/
		HelperFunctions help = HelperFunctions();
		vector<string> instructions = help.splitCommand(command);
		string arg = instructions[0];

		if (instructions.size() == 1)
		{

			/* creates */
			if (arg == "create")
			{
				if (nodeInfo.getStatus() == true)
				{
					cout << "Sorry but this node is already on the ring\n";
				}
				else
				{
					thread first(create, ref(nodeInfo));
					first.detach();
				}
			}

			/* leaves */
			else if (arg == "leave")
			{
				leave(nodeInfo);
				nodeInfo.sp.closeSocket();
				return;
			}

			/* print current port number */
			else if (arg == "port")
			{
				cout << nodeInfo.sp.getPortNumber() << endl;
			}

			/* print keys present in this node */
			else if (arg == "print")
			{
				if (nodeInfo.getStatus() == false)
				{
					cout << "Sorry this node is not in the ring\n";
				}
				else
					nodeInfo.printKeys();
			}

			else
			{
				cout << "Invalid Command\n";
			}
		}
	}
}
