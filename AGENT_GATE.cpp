//
// AGENT_GATE
// ==========
// This Service Interface Function Block provides a gateway to the
// Fault Diagnostic Engine (FDE). It operates within the Diagnostic
// Point DP Composite Function Block (CFB).
//
// AUT University - 2017-2021
//
// Documentation
// =============
// This FORTE Library Element was exported from 4DIAC using the Export
// filter. It was then customised extensively to create functionality
// beyond that possible within the 4DIAC IDE. Therefore, be careful if
// you attempt to export it again ;-)
//
// Revision History
// ================
// 00.00.2019 BRD Original version. 
// 24.02.2020 BRD Refactored and exported from 4DIAC.
// 15.08.2020 BRD Extended to include event trapping for the fault diagnostic
//                engine.
// 17.02.2021 BRD Corrected passThrough() handling of Boolean values.
// 19.02.2021 BRD Added epoch timestamps to the data packets. The TRIGGER
//                function also returns a timestamp of when the event
//                and data was triggered on the function block the DP
//                is triggering.
//
// Declarations
// ============
#include "AGENT_GATE.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "AGENT_GATE_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_AGENT_GATE, g_nStringIdAGENT_GATE)

const CStringDictionary::TStringId FORTE_AGENT_GATE::scm_anDataInputNames[] = {g_nStringIdDATA_IN_INT, g_nStringIdDATA_IN_LINT, g_nStringIdDATA_IN_REAL, g_nStringIdDATA_IN_LREAL, g_nStringIdDATA_IN_STRING, g_nStringIdDATA_IN_WSTRING, g_nStringIdDATA_IN_BOOL, g_nStringIdDATA_TYPE, g_nStringIdADDRESS, g_nStringIdPORT, g_nStringIdINST_ID};

const CStringDictionary::TStringId FORTE_AGENT_GATE::scm_anDataInputTypeIds[] = {g_nStringIdINT, g_nStringIdLINT, g_nStringIdREAL, g_nStringIdLREAL, g_nStringIdSTRING, g_nStringIdWSTRING, g_nStringIdBOOL, g_nStringIdINT, g_nStringIdSTRING, g_nStringIdLINT, g_nStringIdINT};

const CStringDictionary::TStringId FORTE_AGENT_GATE::scm_anDataOutputNames[] = {g_nStringIdDATA_OUT_INT, g_nStringIdDATA_OUT_LINT, g_nStringIdDATA_OUT_REAL, g_nStringIdDATA_OUT_LREAL, g_nStringIdDATA_OUT_STRING, g_nStringIdDATA_OUT_WSTRING, g_nStringIdDATA_OUT_BOOL};

const CStringDictionary::TStringId FORTE_AGENT_GATE::scm_anDataOutputTypeIds[] = {g_nStringIdINT, g_nStringIdLINT, g_nStringIdREAL, g_nStringIdLREAL, g_nStringIdSTRING, g_nStringIdWSTRING, g_nStringIdBOOL};

const TForteInt16 FORTE_AGENT_GATE::scm_anEIWithIndexes[] = {0, -1, 5};
const TDataIOID FORTE_AGENT_GATE::scm_anEIWith[] = {10, 9, 8, 7, 255, 0, 1, 2, 3, 4, 5, 6, 255};
const CStringDictionary::TStringId FORTE_AGENT_GATE::scm_anEventInputNames[] = {g_nStringIdSTART, g_nStringIdPOLL, g_nStringIdDATA_IN};

const TDataIOID FORTE_AGENT_GATE::scm_anEOWith[] = {0, 1, 2, 3, 4, 5, 6, 255};
const TForteInt16 FORTE_AGENT_GATE::scm_anEOWithIndexes[] = {0, -1};
const CStringDictionary::TStringId FORTE_AGENT_GATE::scm_anEventOutputNames[] = {g_nStringIdDATA_OUT};

const SFBInterfaceSpec FORTE_AGENT_GATE::scm_stFBInterfaceSpec = {
  3,  scm_anEventInputNames,  scm_anEIWith,  scm_anEIWithIndexes,
  1,  scm_anEventOutputNames,  scm_anEOWith, scm_anEOWithIndexes,  11,  scm_anDataInputNames, scm_anDataInputTypeIds,
  7,  scm_anDataOutputNames, scm_anDataOutputTypeIds,
  0, 0
};

using std::cout;
using std::string;
using std::to_string;
using std::stoi;
using std::stod;
using std::stof;

using std::cout; using std::endl;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

//
// executeEvent()
// ==============
// This is the controller which coordinates all the functionality
// of the AGENT_GATE. It is the main entry point that FORTE calls
// during the normal execution cycle of the function block 
// application.
//
void FORTE_AGENT_GATE::executeEvent(int pa_nEIID){
	int dataType = 0;
	string dataValue = "";
	string packet = "";
	long unsigned int dataLen = 0;
	auto timeStamp = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count(); 	
 	
	if (!client.isConnected()) {
		if (DP_instance != -1) {
			// Initialisation of the function block has completed. Now
		 	// connect as a client to the fault diagnostic engine.
			long int listenerPort = 0;
 			listenerPort = PORT();
 			char serverAddress[32] = {0};
 			ADDRESS().toString(serverAddress, 32);
   		// FORTE parameter strings have leading and terminating single-quote characters in them 
   		// so remove them from the server address just created.
 		  	for(int ptr = 1; ptr <= 32; ptr++) {
				serverAddress[ptr - 1] = serverAddress[ptr];
				if ((ptr > 1 ) && (serverAddress[ptr] == '\'')) {
					serverAddress[ptr - 1] = '\0';
					break;
				}
			}
			
			if (!client.connectToServer(serverAddress, listenerPort)) {	
				//cout << "DP_" << INST_ID() << " connected to the engine\n";
		//	} else {
				cout << "DP_" << to_string(DP_instance) << " cannot connect to the engine at " 
  		           << serverAddress << " via listenerPort " << listenerPort
				     << ". " << client.getLastErrorMessage() << "\n";
			}
		}
	}		

	switch(pa_nEIID){
	case scm_nEventSTARTID:
		// Load the static configuration parameters.
		DP_instance = INST_ID();
 		break;
 
   case scm_nEventPOLLID:  
 	 	if (client.isConnected()) {
   		// Poll the server to signal that the agent is ready.
   		timeStamp = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
   		client.sendPacket(START_OF_PACKET + to_string(POLL_AGENT) + FIELD_SEPARATOR 
    			               + to_string(DP_instance) + FIELD_SEPARATOR 
    			               + to_string(timeStamp) + FIELD_SEPARATOR + END_OF_PACKET);
  
     		// Check for a returing data packet that the agent may have sent. This can either be
   		// a command to execute or it could be a data value or event to inject into the 
   		// function block this DP is connected to.
   		dataValue = "";                  
   		packet = client.recvPacket();
   		if (packet.length() > 0) {
   			cout << "DP_" << to_string(DP_instance) <<" packet received = [ " << packet << " ]\n";
 	 			size_t ptrStart = 1;
   			size_t ptrEnd = -1;
  				ptrEnd = packet.find("|");
	 			if (ptrEnd > (size_t) 0) {
	 				// Extract the command being sent by the agent.
	 			  	int command = stoi(packet.substr(ptrStart, ptrEnd - 1));
	 				cout << "DP_" << to_string(DP_instance) << " command received [ " << command << " ]\n";		 				
	 				
	 				switch (command) {		 				
 					case TRIGGER_DATA_VALUE: 
 						ptrStart = ptrEnd + 1;
 						ptrEnd = packet.find(FIELD_SEPARATOR, ptrStart);
 						if (ptrEnd > (size_t) 0) {
 							dataLen = stoi(packet.substr(ptrStart, ptrEnd - 1));
 							//cout << "Length of data " << to_string(dataLen) << "\n";
 							if (dataLen > 0) {
 								dataValue = packet.substr(ptrEnd + 1, dataLen);
 							}
 						}
 								
 						timeStamp = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count(); 	
  						//trigger(dataValue);
   					packet = START_OF_PACKET + to_string(TIMESTAMP) + FIELD_SEPARATOR 
    					         + to_string(DP_instance) + FIELD_SEPARATOR
    			      			+ to_string(timeStamp) + FIELD_SEPARATOR + END_OF_PACKET;
    			      trigger(dataValue);				
   					client.sendPacket(packet);
   					cout << "DP_" << to_string(DP_instance) << " trigger data [" << dataValue << " ]"
   						  << " Timestamp sent back [" << to_string(timeStamp) << "]\n"
   						  << " in packet  [ " << packet << " ]\n";
   					break;
  						
  					case TRIGGER_EVENT:
  						timeStamp = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count(); 	
   					packet = START_OF_PACKET + to_string(TIMESTAMP) + FIELD_SEPARATOR 
    					         + to_string(DP_instance) + FIELD_SEPARATOR
    			      			+ to_string(timeStamp) + FIELD_SEPARATOR + END_OF_PACKET;
    			      trigger("");
   					client.sendPacket(packet);
   					cout << "DP_" << to_string(DP_instance) << " trigger event. "
   						  << " Timestamp sent back [" << to_string(timeStamp) << "]\n"
   						  << " in packet  [ " << packet << " ]\n";
  						break;
  							
 					case PASSTHROUGH_ENABLED:
 						// The agent is switching this DP back to passthrough mode.
 						cout << "DP_" << to_string(DP_instance) << " mode change - gateOpen() (passthrough mode re-enabled)\n";
 						mode = PASSTHROUGH_ENABLED;
 						dataValue = "";
 						break;
 	 				}
	 			}	
	 		}
	 	}
	 	break;		
		 	
//		 	if (dataValue.length() > 0) {
    			// Inject the data into the function block application and trigger an event.
 //   			auto timeStamp = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
  // 			trigger(dataValue);
    			// Return the time that this event was triggered back to the agent.
    		//	packet = START_OF_PACKET + to_string(TIMESTAMP) + FIELD_SEPARATOR 
    		//	         + to_string(DP_instance) + FIELD_SEPARATOR
    		//	         + to_string(timeStamp) + FIELD_SEPARATOR + END_OF_PACKET;
    		//	client.sendPacket(packet);
    		//	cout << "timeStamp sent back = [" << timeStamp << "] packet " << packet << "\n";                  
  // 		}
 //   	}
    	//} else if (mode == PASSTHROUGH_ENABLED) {
    	//	cout << "Passthrough enabled on DP_" << to_string(DP_instance) << "\n";	
    	//	}
 //  	break;	
	
	case scm_nEventDATA_INID:
		// The DP has captured either an event or a data input from the function block that this
		// DP is connected to on its input (left-hand) side. 
		if (mode == PASSTHROUGH_ENABLED) {
			// The DP is in Passthrough mode so pass this value transparently through. If the
			// DP had been gated on its left-hand side, it would have been in trigger-enabled 
			// mode so any incoming events or data must be blocked. See the polling section
			// above where the triggering occurs. 
			dataValue = passThrough();
			cout << "DP_" << to_string(DP_instance) << " event trigger. dataValue = [ " << dataValue << " ]\n";
		
	    	if (client.isConnected()) {
	    		// There is a connection open to the server so send a diagnostic packet
	    		// containing this data. If the diagnostic point is monitoring an event only, then
	    		// the dataValue will be blank and the data length will be zero.
	    		//
	    		timeStamp = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
	    		packet = START_OF_PACKET + to_string(SAMPLED_DATA) + FIELD_SEPARATOR + to_string(DP_instance)
	    								+ FIELD_SEPARATOR + to_string(timeStamp)
   			                  + FIELD_SEPARATOR + to_string(dataValue.length())
   			                  + FIELD_SEPARATOR  + dataValue
   			                  + FIELD_SEPARATOR + END_OF_PACKET;
   			//cout << "packet = [" <<  packet << "\n";		                  
	    		//client.sendPacket(START_OF_PACKET + to_string(SAMPLED_DATA) + FIELD_SEPARATOR + to_string(DP_instance)
   			//                  + FIELD_SEPARATOR + to_string(dataValue.length()) + FIELD_SEPARATOR  + dataValue + FIELD_SEPARATOR + END_OF_PACKET);
   			client.sendPacket(packet);
   		   // Check for a reply from the server.	    		
	    		packet = client.recvPacket();
   			if (packet.length() > 0) {
   				cout << "DP_" << to_string(DP_instance) << " received packet = [" << packet << "\n";
 	 				size_t ptrStart = 1;
   				size_t ptrEnd = -1;
  					ptrEnd = packet.find("|");
	 				if (ptrEnd > (size_t) 0) {
	 					// Extract the command being sent by the agent.
	 			   	int command = stoi(packet.substr(ptrStart, ptrEnd - 1));
	 					cout << "[" << command << "]\n";
	 					
	 					switch (command) {
	 					case TRIGGER_ENABLED:
	 						// The agent has requested the DP to disable Passthrough mode. Values will be supplied by the
	 						// agent, not the function block this DP is connected to until further notice.
							cout << "\n\nDP_" << to_string(DP_instance) << " mode change - gateClose() (agent will supply data from now on)\n";
							mode = TRIGGER_ENABLED;			
	 						break;

		 				case TRIGGER_DATA_VALUE:
							if (mode == PASSTHROUGH_ENABLED) {
 								// The passthrough disable command must have been missed previously
 								// so enable the agent trigger anyway. The agent will re-synchronise.
 								cout << "\n\nDP_" << to_string(DP_instance) 
 								     << " unexpected Mode change - implied TRIGGER_ENABLED and gateClose() (agent will supply data from now on.)\n";
 								mode = TRIGGER_ENABLED;
 							}
 							break;
 							
 						case PASSTHROUGH_ENABLED:
 							// The agent is re-enabling Passthrough mode and will no longer
 							// supply trigger inputs.
 						   cout << "\n\nDP_" << to_string(DP_instance) << " mode change - gateOpen() (passthrough mode re-enabled)\n";
 						   mode = PASSTHROUGH_ENABLED;
 						   break;
						}
 					}
 				}		
    		}
		}
	}
}

//
// passThrough()
// =============
// Pass events and data directly through this function block from other 
// function blocks in the same application. It returns a string value of 
// the data that is later sent to the fault diagnostic engine. The output
// event is also fired.
//
// The data type specified on the parameter port DATA_TYPE is used
// to determine how to route the data to the correct output port. 
//
string FORTE_AGENT_GATE::passThrough(){
	int dataType = DATA_TYPE();
	char tempString[100] = {0};  //RA_BRD can we make this dynamic so it is not limited to 100 characters?
	string dataValue = "";

   switch (dataType) {
   case DATATYPE_EVENT:
   	cout << "DP_" << to_string(DP_instance) << " passthrough event fired\n";
      dataValue = "T"; //BRD ??
      break;

   case DATATYPE_INT:
   	dataValue = to_string(DATA_IN_INT());
  		DATA_OUT_INT() = DATA_IN_INT();
  		break;
   	
   case DATATYPE_LINT:
   	dataValue = to_string(DATA_IN_LINT());
   	DATA_OUT_LINT() = DATA_IN_LINT();
   	break;
   				
   case DATATYPE_REAL:
   	dataValue = to_string(DATA_IN_REAL());
   	DATA_OUT_REAL() = DATA_IN_REAL();
   	break; 
   		
   case DATATYPE_LREAL:
   	dataValue = to_string(DATA_IN_LREAL());
   	DATA_OUT_LREAL() = DATA_IN_LREAL();
   	break;
   		
	case DATATYPE_STRING:
		// RA_BRD this needs testing.
		DATA_IN_STRING().toString(tempString, DATA_IN_STRING().length());
 		dataValue = tempString; 
 		DATA_OUT_STRING() = DATA_IN_STRING();
		break; 
		
	case DATATYPE_WSTRING:
		// RA_BRD this needs testing.
		DATA_IN_WSTRING().toString(tempString, DATA_IN_WSTRING().length());
		dataValue = tempString; 
		DATA_OUT_WSTRING() = DATA_IN_WSTRING();
		break;
	
	case DATATYPE_BOOL:
		DATA_OUT_BOOL() = DATA_IN_BOOL();
		if (DATA_OUT_BOOL()) {
			dataValue = "T";
		} else {
			dataValue = "F";
		}
		break;	
   }
   sendOutputEvent(scm_nEventDATA_OUTID);
   return dataValue;
} 

//
// trigger()
// =========
// Test data supplied by the agent is passed directly to the
// correct output port after converting it to an appropriate
// data type. Fire the output event.
//
// The data type specified on the parameter port DATA_TYPE is used
// to determine how to route the data to the correct output port. 
//
void FORTE_AGENT_GATE::trigger(string dataValue){ 	
	int dataType = DATA_TYPE();
   switch (dataType) {
   case DATATYPE_EVENT:	
		// There is no data input since this is just an event
		// being triggered.
      break;
 
   case DATATYPE_INT:
 		DATA_OUT_INT() = stoi(dataValue);
  		break;
   	
   case DATATYPE_LINT:
	  	DATA_OUT_LINT() = stol(dataValue);
   	break;
   				
   case DATATYPE_REAL:
 	 	DATA_OUT_REAL() = stof(dataValue);
   	break; 
   		
   case DATATYPE_LREAL:
	  	DATA_OUT_LREAL() = stoll(dataValue);
   	break;
   		
	case DATATYPE_STRING:
		// RA_BRD this needs testing.
		// DATA_IN_STRING().toString(tempString, DATA_IN_STRING().length());
 		// dataValue = tempString; 
 		//	DATA_OUT_STRING() = dataValue
		break; 
		
	case DATATYPE_WSTRING:
		// RA_BRD this needs testing.
	//	DATA_OUT_WSTRING() = dataValue;
		break;
	
	case DATATYPE_BOOL:
		if (dataValue == "T") {
			DATA_OUT_BOOL() = true;	
		} else {
			DATA_OUT_BOOL() = false;
		}	
		break;	
   }
   sendOutputEvent(scm_nEventDATA_OUTID);
}

