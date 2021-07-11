/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x!
 ***
 *** Name: DP
 *** Description: Diagnostic Point
 *** Version: 
 ***     1.0: 2020-05-28/Badger - AUT - 
 *************************************************************************/

#include "DP.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "DP_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_DP, g_nStringIdDP)

const CStringDictionary::TStringId FORTE_DP::scm_anDataInputNames[] = {g_nStringIdDATA_IN_INT, g_nStringIdDATA_IN_LINT, g_nStringIdDATA_IN_REAL, g_nStringIdDATA_IN_LREAL, g_nStringIdDATA_IN_STRING, g_nStringIdDATA_IN_WSTRING, g_nStringIdDATA_IN_BOOL, g_nStringIdDATA_TYPE, g_nStringIdPOLL_TIME, g_nStringIdADDRESS, g_nStringIdPORT, g_nStringIdINST_ID};

const CStringDictionary::TStringId FORTE_DP::scm_anDataInputTypeIds[] = {g_nStringIdINT, g_nStringIdLINT, g_nStringIdREAL, g_nStringIdLREAL, g_nStringIdSTRING, g_nStringIdWSTRING, g_nStringIdBOOL, g_nStringIdINT, g_nStringIdTIME, g_nStringIdSTRING, g_nStringIdLINT, g_nStringIdINT};

const CStringDictionary::TStringId FORTE_DP::scm_anDataOutputNames[] = {g_nStringIdDATA_OUT_INT, g_nStringIdDATA_OUT_LINT, g_nStringIdDATA_OUT_REAL, g_nStringIdDATA_OUT_LREAL, g_nStringIdDATA_OUT_STRING, g_nStringIdDATA_OUT_WSTRING, g_nStringIdDATA_OUT_BOOL};

const CStringDictionary::TStringId FORTE_DP::scm_anDataOutputTypeIds[] = {g_nStringIdINT, g_nStringIdLINT, g_nStringIdREAL, g_nStringIdLREAL, g_nStringIdSTRING, g_nStringIdWSTRING, g_nStringIdBOOL};

const TForteInt16 FORTE_DP::scm_anEIWithIndexes[] = {0, 5};
const TDataIOID FORTE_DP::scm_anEIWith[] = {9, 10, 11, 8, 255, 6, 7, 5, 4, 3, 2, 1, 255};
const CStringDictionary::TStringId FORTE_DP::scm_anEventInputNames[] = {g_nStringIdSTART, g_nStringIdDATA_IN};

const TDataIOID FORTE_DP::scm_anEOWith[] = {6, 0, 1, 2, 3, 4, 5, 255};
const TForteInt16 FORTE_DP::scm_anEOWithIndexes[] = {0, -1};
const CStringDictionary::TStringId FORTE_DP::scm_anEventOutputNames[] = {g_nStringIdDATA_OUT};

const SFBInterfaceSpec FORTE_DP::scm_stFBInterfaceSpec = {
  2,  scm_anEventInputNames,  scm_anEIWith,  scm_anEIWithIndexes,
  1,  scm_anEventOutputNames,  scm_anEOWith, scm_anEOWithIndexes,  12,  scm_anDataInputNames, scm_anDataInputTypeIds,
  7,  scm_anDataOutputNames, scm_anDataOutputTypeIds,
  0, 0
};


const SCFB_FBInstanceData FORTE_DP::scm_astInternalFBs[] = {
  {g_nStringIdE_CYCLE, g_nStringIdE_CYCLE},
  {g_nStringIdAGENT_GATE, g_nStringIdAGENT_GATE},
};

const SCFB_FBConnectionData FORTE_DP::scm_astEventConnections[] = {
  {GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdSTART), -1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_CYCLE, g_nStringIdSTART), 0},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_CYCLE, g_nStringIdEO), 0, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdAGENT_GATE, g_nStringIdPOLL), 1},
  {GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdDATA_IN), -1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdAGENT_GATE, g_nStringIdDATA_IN), 1},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdAGENT_GATE, g_nStringIdDATA_OUT), 1, GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdDATA_OUT), -1},
};

const SCFB_FBFannedOutConnectionData FORTE_DP::scm_astFannedOutEventConnections[] = {
  {0, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdAGENT_GATE, g_nStringIdSTART), 1},
};

const SCFB_FBConnectionData FORTE_DP::scm_astDataConnections[] = {
  {GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdPOLL_TIME), -1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdE_CYCLE, g_nStringIdDT), 0},
  {GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdDATA_IN_INT), -1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdAGENT_GATE, g_nStringIdDATA_IN_INT), 1},
  {GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdDATA_IN_LINT), -1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdAGENT_GATE, g_nStringIdDATA_IN_LINT), 1},
  {GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdDATA_IN_REAL), -1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdAGENT_GATE, g_nStringIdDATA_IN_REAL), 1},
  {GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdDATA_IN_LREAL), -1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdAGENT_GATE, g_nStringIdDATA_IN_LREAL), 1},
  {GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdDATA_IN_STRING), -1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdAGENT_GATE, g_nStringIdDATA_IN_STRING), 1},
  {GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdDATA_IN_WSTRING), -1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdAGENT_GATE, g_nStringIdDATA_IN_WSTRING), 1},
  {GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdDATA_IN_BOOL), -1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdAGENT_GATE, g_nStringIdDATA_IN_BOOL), 1},
  {GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdDATA_TYPE), -1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdAGENT_GATE, g_nStringIdDATA_TYPE), 1},
  {GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdADDRESS), -1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdAGENT_GATE, g_nStringIdADDRESS), 1},
  {GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdPORT), -1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdAGENT_GATE, g_nStringIdPORT), 1},
  {GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdINST_ID), -1, GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdAGENT_GATE, g_nStringIdINST_ID), 1},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdAGENT_GATE, g_nStringIdDATA_OUT_INT), 1, GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdDATA_OUT_INT), -1},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdAGENT_GATE, g_nStringIdDATA_OUT_LINT), 1, GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdDATA_OUT_LINT), -1},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdAGENT_GATE, g_nStringIdDATA_OUT_REAL), 1, GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdDATA_OUT_REAL), -1},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdAGENT_GATE, g_nStringIdDATA_OUT_LREAL), 1, GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdDATA_OUT_LREAL), -1},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdAGENT_GATE, g_nStringIdDATA_OUT_STRING), 1, GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdDATA_OUT_STRING), -1},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdAGENT_GATE, g_nStringIdDATA_OUT_WSTRING), 1, GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdDATA_OUT_WSTRING), -1},
  {GENERATE_CONNECTION_PORT_ID_2_ARG(g_nStringIdAGENT_GATE, g_nStringIdDATA_OUT_BOOL), 1, GENERATE_CONNECTION_PORT_ID_1_ARG(g_nStringIdDATA_OUT_BOOL), -1},
};

const SCFB_FBNData FORTE_DP::scm_stFBNData = {
  2, scm_astInternalFBs,
  4, scm_astEventConnections,
  1, scm_astFannedOutEventConnections,
  19, scm_astDataConnections,
  0, 0,
  0, 0
};


