#ifndef NIOCLIENT_H
#define NIOCLIENT_H

#include <string.h> 
using std::string;

class NIOclient {
	//
	// Module-level declarations
	// =========================
	private:
		string lastErrorMessage = "";
		bool haveConnection = false;
		int clientSocket = 0;
 
 	//
 	// Public functions
 	// ================
	public:
		bool connectToServer(string serverAddress, long int port);
		string getLastErrorMessage();
		string recvPacket();
		bool sendPacket(string msg);
		bool isConnected();
 };

#endif 
