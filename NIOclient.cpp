//
// NON-BLOCKING TCP CLIENT
// =======================
// Non-blocking TCP client library for use with FORTE function blocks.
//
// AUT University - 2019-2020
// 
// Version history
// ===============
// 04.01.2020 BRD Original version.
// 07.01.2020 BRD Implemented non-blocking flow control on the sockets.
//  
#include <iostream>
#include <stdio.h>	
#include <string.h> 
#include <stdlib.h> 
#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <string>
#include <fcntl.h>

#include "NIOclient.h"

using std::cout;
using std::string;
using std::to_string;
using std::string;

//
// connectToServer()
// =================
// Establishes an IP connection via a listener socket on a remote server.
//
// serverAddress	Fully-qualified network URL for this server
//						instance that non-blocking clients can connect
//						to. Either a name such as "localhost" or an
//						IP address such as "127.0.0.1".
//
// listenerPort	The socket port that the server is listening on
//						for incoming connections. This is a handover
//						type socket. Once a client connects, the server
//						will hand over the connection to an individual
//						session socket that will manage the traffic for
//						that client for the duration of the session.
//
// returns   		Boolean true if a session can be established. If it 
//						cannot connect, getlastErrorMessage() returns details
//						of the problem.
//
bool NIOclient::connectToServer(string serverAddress, long int listenerPort) {
	struct sockaddr_in address, server_addr;
			
	//cout << "Connecting to " << serverAddress << " on port " << to_string(listenerPort) << "\n";
	
	// RA_BRD - need to modularise this, sorting out the CIEC_STRING conversion issue.
	//
	// FORTE parameter strings have leading and terminating single-quote characters in them 
   // so remove them from the server address just created.
	//long int listenerPort = 0;
   //listenerPort = PORT();
  	// char tempServerAddress[32] = {0};
   //serverAddress.toString(tempServerAddress, 32);
 
   //for(int ptr = 1; ptr <= 32; ptr++) {
	//	tempServerAddress[ptr - 1] = tempServerAddress[ptr];
	//	if ((ptr > 1 ) && (tempServerAddress[ptr] == '\'')) {
	//		tempServerAddress[ptr - 1] = '\0';
	//		break;
	//	}
	//}
		
	lastErrorMessage = "";
	haveConnection = false;
	if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0 )) < 0) {
		lastErrorMessage = "Cannot create socket"; 
   } else {
		// Connect to the server.
		memset((char *) &address, 0, sizeof(address));
		server_addr.sin_family = AF_INET;
		server_addr.sin_port = htons((uint16_t) listenerPort);

		// Convert an IPv4 network address in the format ddd.ddd.ddd.ddd from text to binary form. Use
		// AF_INET6 instead of AF_INET if this is an IPv6 address. Note that the second parameter of the
		// inet_pton() function requires a character pointer to a string constant. The next line converts
		// the serverAddress parameter to a pointer.  
		const char *ptr_serverAddress = serverAddress.c_str();
		
		if (inet_pton(AF_INET, ptr_serverAddress, &server_addr.sin_addr) <= 0) {
			lastErrorMessage = "Invalid address or address not supported";
		} else {
			if (connect(clientSocket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
				lastErrorMessage = "Connection failed";
			} else {
			
				int flags = fcntl(clientSocket, F_GETFL, 0);
				fcntl(clientSocket, F_SETFL, flags | O_NONBLOCK);				
				haveConnection = true;
			}
		}
	}
	return haveConnection;
}

//
// getLastErrorMessage()
// =====================
// Returns the last error message logged by one of
// the functions in this class.
//
string NIOclient::getLastErrorMessage() {
	return lastErrorMessage;
}

//
// isConnected()
// =============
bool NIOclient::isConnected() {
	return haveConnection;
}

//
// sendPacket()
// ============
// Sends a packet of data to the remote server that was previously
// connected to using createServerConnection():
//
// msg       String to be sent to the server. Since the connection was opened as a stream, there
//   		    no maximum size for this data packet.
//
// returns   True if the message was sent successfully.
//
bool NIOclient::sendPacket(string msg) {
	if (haveConnection) {
		send(clientSocket, msg.c_str(), msg.length(), 0);
		return true;
	} else {
		lastErrorMessage = "Cannot send data packet using sendPacket(): no connection is open.";
		return false;	
	}	
}	

//
// recvPacket()
// ============
string NIOclient::recvPacket() {
	if (haveConnection) {
		char buffer[1024] = {0};
		read(clientSocket, buffer, 1024);
		return buffer;
	} else {
		lastErrorMessage = "Cannot retrieve data packet using recvPacket(): no connection is open.";
		return "";	
	}		
}

