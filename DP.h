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

#ifndef _DP_H_
#define _DP_H_

#include <cfb.h>
#include <typelib.h>
#include <forte_lint.h>
#include <forte_bool.h>
#include <forte_real.h>
#include <forte_string.h>
#include <forte_time.h>
#include <forte_int.h>
#include <forte_wstring.h>
#include <forte_lreal.h>

class FORTE_DP: public CCompositeFB{
  DECLARE_FIRMWARE_FB(FORTE_DP)

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

  CIEC_TIME &POLL_TIME() {
    return *static_cast<CIEC_TIME*>(getDI(8));
  };

  CIEC_STRING &ADDRESS() {
    return *static_cast<CIEC_STRING*>(getDI(9));
  };

  CIEC_LINT &PORT() {
    return *static_cast<CIEC_LINT*>(getDI(10));
  };

  CIEC_INT &INST_ID() {
    return *static_cast<CIEC_INT*>(getDI(11));
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
  static const TEventID scm_nEventDATA_INID = 1;
  static const TForteInt16 scm_anEIWithIndexes[];
  static const TDataIOID scm_anEIWith[];
  static const CStringDictionary::TStringId scm_anEventInputNames[];

  static const TEventID scm_nEventDATA_OUTID = 0;
  static const TForteInt16 scm_anEOWithIndexes[];
  static const TDataIOID scm_anEOWith[];
  static const CStringDictionary::TStringId scm_anEventOutputNames[];

  static const SFBInterfaceSpec scm_stFBInterfaceSpec;

   FORTE_FB_DATA_ARRAY(1, 12, 7, 0);

  static const SCFB_FBInstanceData scm_astInternalFBs[];

  static const SCFB_FBConnectionData scm_astEventConnections[];

  static const SCFB_FBFannedOutConnectionData scm_astFannedOutEventConnections[];

  static const SCFB_FBConnectionData scm_astDataConnections[];
  static const SCFB_FBNData scm_stFBNData;

public:
  COMPOSITE_FUNCTION_BLOCK_CTOR(FORTE_DP){
  };

  virtual ~FORTE_DP(){};

};

#endif //close the ifdef sequence from the beginning of the file

