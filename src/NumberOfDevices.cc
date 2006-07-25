#include "CalibFormats/SiStripObjects/interface/NumberOfDevices.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include <iomanip>

using namespace std;

// -----------------------------------------------------------------------------
//
void NumberOfDevices::clear() {
  nFecCrates_ = 0;
  nFecSlots_ = 0;
  nFecRings_ = 0;
  nCcuAddrs_ = 0;
  nCcuChans_ = 0;
  nApvs_ = 0;
  nDcuIds_ = 0;
  nDetIds_ = 0;
  nApvPairs_ = 0;
  nFedIds_ = 0;
  nFedChans_ = 0;
  nDcus_ = 0;
  nMuxes_ = 0;
  nPlls_ = 0;
  nLlds_ = 0;
}

// -----------------------------------------------------------------------------
//
void NumberOfDevices::print( stringstream& ss ) const {
  ss.str("");
  ss << "[NumberOfDevices::print] Number of devices found: " 
     << "  FEC crates: " << nFecCrates_
     << "  FEC slots: " << nFecSlots_
     << "  FEC rings: " << nFecRings_
     << "  CCU addrs: " << nCcuAddrs_
     << "  CCU chans: " << nCcuChans_
     << "  APVs: " << nApvs_
     << "  DCU ids: " << nDcuIds_
     << "  DET ids: " << nDetIds_
     << "  APV pairs: " << nApvPairs_
     << "  FED channels: " << nFedChans_
     << "  DCUs: " << nDcus_
     << "  MUXes: " << nMuxes_
     << "  PLLs: " << nPlls_
     << "  LLDs: " << nLlds_;
}
