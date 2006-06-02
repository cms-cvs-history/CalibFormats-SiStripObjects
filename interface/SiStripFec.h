// Last commit: $Id$
// Latest tag:  $Name$
// Location:    $Source$

#ifndef CalibFormats_SiStripObjects_SiStripFec_H
#define CalibFormats_SiStripObjects_SiStripFec_H

#include "CalibFormats/SiStripObjects/interface/SiStripRing.h"
#include "CondFormats/SiStripObjects/interface/FedChannelConnection.h"
#include <boost/cstdint.hpp>
#include <vector>

/** 
    \class SiStripFec
    \author R.Bainbridge
*/
class SiStripFec {

 public: 

  /** */
  SiStripFec( const FedChannelConnection& conn )
    : fecSlot_( conn.fecSlot() ), rings_() { addDevices( conn ); }
  
  /** */
  ~SiStripFec() {;}
  
  /** */
  inline const std::vector<SiStripRing>& rings() const;

  /** */
  inline const uint16_t& fecSlot() const;

  /** */
  void addDevices( const FedChannelConnection& conn );
  
 private:

  /** */
  SiStripFec() {;}

  /** */
  uint16_t fecSlot_;

  /** */
  std::vector<SiStripRing> rings_;

};

// ---------- inline methods ----------

const std::vector<SiStripRing>& SiStripFec::rings() const { return rings_; }
const uint16_t& SiStripFec::fecSlot() const { return fecSlot_; }

#endif // CalibTracker_SiStripObjects_SiStripFec_H


