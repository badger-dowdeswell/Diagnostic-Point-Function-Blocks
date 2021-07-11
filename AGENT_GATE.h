//
// AGENT_GATE.h
// ============
//
#ifndef _AGENT_GATE_H_
#define _AGENT_GATE_H_

#include <iostream>
#include <stdio.h>

#include <chrono>
#include <sys/time.h>
#include <ctime>

#include "NIOclient.h"

#include <funcbloc.h>
#include <forte_lint.h>
#include <forte_bool.h>
#include <forte_real.h>
#include <forte_string.h>
#include <forte_int.h>
#include <forte_wstring.h>
#include <forte_lreal.h>

class FORTE_AGENT_GATE: public CFunctionBlock{
  DECLARE_FIRMWARE_FB(FORTE_AGENT_GATE)

private:
  static const CStringDictionary::TStringId scm_anDataInputNames[];
  static const CStringDictionary::TStringId scm_anDataInputTypeIds[];
  CIEC_INT &DATA_IN_INT() {
    return *static_cast<CIEC_INT*>(getDI(0));
  };

  CIEC_LINT &DATA_IN_LINT() {
    return *static_cast<CIEC_LINT*>(getDI(1));
  };

  CIEC_REAL &DATA_IN_REAL() {
    return *static_cast<CIEC_REAL*>(getDI(2));
  };

  CIEC_LREAL &DATA_IN_LREAL() {
    return *static_cast<CIEC_LREAL*>(getDI(3));
  };

  CIEC_STRING &DATA_IN_STRING() {
    return *static_cast<CIEC_STRING*>(getDI(4));
  };

  CIEC_WSTRING &DATA_IN_WSTRING() {
    return *static_cast<CIEC_WSTRING*>(getDI(5));
  };

  CIEC_BOOL &DATA_IN_BOOL() {
    return *static_cast<CIEC_BOOL*>(getDI(6));
  };

  CIEC_INT &DATA_TYPE() {
    return *static_cast<CIEC_INT*>(getDI(7));
  };

  CIEC_STRING &ADDRESS() {
    return *static_cast<CIEC_STRING*>(getDI(8));
  };

  CIEC_LINT &PORT() {
    return *static_cast<CIEC_LINT*>(getDI(9));
  };

  CIEC_INT &INST_ID() {
    return *static_cast<CIEC_INT*>(getDI(10));
  };

  static const CStringDictionary::TStringId scm_anDataOutputNames[];
  static const CStringDictionary::TStringId scm_anDataOutputTypeIds[];
  CIEC_INT &DATA_OUT_INT() {
    return *static_cast<CIEC_INT*>(getDO(0));
  };

  CIEC_LINT &DATA_OUT_LINT() {
    return *static_cast<CIEC_LINT*>(getDO(1));
  };

  CIEC_REAL &DATA_OUT_REAL() {
    return *static_cast<CIEC_REAL*>(getDO(2));
  };

  CIEC_LREAL &DATA_OUT_LREAL() {
    return *static_cast<CIEC_LREAL*>(getDO(3));
  };

  CIEC_STRING &DATA_OUT_STRING() {
    return *static_cast<CIEC_STRING*>(getDO(4));
  };

  CIEC_WSTRING &DATA_OUT_WSTRING() {
    return *static_cast<CIEC_WSTRING*>(getDO(5));
  };

  CIEC_BOOL &DATA_OUT_BOOL() {
    return *static_cast<CIEC_BOOL*>(getDO(6));
  };

  static const TEventID scm_nEventSTARTID = 0;
  static const TEventID scm_nEventPOLLID = 1;
  static const TEventID scm_nEventDATA_INID = 2;
  static const TForteInt16 scm_anEIWithIndexes[];
  static const TDataIOID scm_anEIWith[];
  static const CStringDictionary::TStringId scm_anEventInputNames[];

  static const TEventID scm_nEventDATA_OUTID = 0;
  static const TForteInt16 scm_anEOWithIndexes[];
  static const TDataIOID scm_anEOWith[];
  static const CStringDictionary::TStringId scm_anEventOutputNames[];

  static const SFBInterfaceSpec scm_stFBInterfaceSpec;

  FORTE_FB_DATA_ARRAY(1, 11, 7, 0);

  void executeEvent(int pa_nEIID);
   
	//
	// Packet structure definitions
	// ============================
	static constexpr const char* START_OF_PACKET = "*";
	static constexpr const char* FIELD_SEPARATOR = "|";
	static constexpr const char* END_OF_PACKET = "&";  
	   
   //
   // Data type definition
   // ====================
	// Used to determine how to route the
  	// correct data though the gate correctly.
 
  	//
  	enum DataTypes {
		DATATYPE_UNDEFINED = -1,
		DATATYPE_EVENT = 0,  
		DATATYPE_INT = 1,
		DATATYPE_LINT = 2,
		DATATYPE_REAL = 3,
		DATATYPE_LREAL = 4,
		DATATYPE_STRING = 5,
		DATATYPE_WSTRING = 6,
		DATATYPE_BOOL = 7	
	};
	
	//
	// Operating modes
	// ===============
	// Signals if the AGENT_GATE instance is passing data through
	// directly or routing values from the external Fault Engine agent.
	// Note that the diagnostic point always starts in passthrough
	// mode.
	//
  	// In the FDE source, these constants are defined in the class 
  	// DiagnosticAgent as the class AgentModes. 
	//
	enum commands {
		UNDEFINED = 0,
		PASSTHROUGH_ENABLED = 1,
		TRIGGER_ENABLED = 2,
		TRIGGER_DATA_VALUE = 3,
		TRIGGER_EVENT = 4,
		POLL_AGENT = 5,
		SAMPLED_DATA = 6,
		TIMESTAMP = 7
	};
	int mode = PASSTHROUGH_ENABLED;
	
	int DP_instance = -1; 
	
	NIOclient client; 
	
	string passThrough();
	void trigger(string dataValue);

public:
  FUNCTION_BLOCK_CTOR(FORTE_AGENT_GATE){
  };

  virtual ~FORTE_AGENT_GATE(){};

};

#endif //close the ifdef sequence from the beginning of the file

