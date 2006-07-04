#ifndef CalibFormats_SiStripObjects_SiStripFecCabling_H
#define CalibFormats_SiStripObjects_SiStripFecCabling_H

#include "CondFormats/SiStripObjects/interface/SiStripFedCabling.h"
#include "CondFormats/SiStripObjects/interface/FedChannelConnection.h"
#include "CalibFormats/SiStripObjects/interface/SiStripFecCrate.h"
#include <boost/cstdint.hpp>
#include <vector>

class NumberOfDevices;

/* 
   @class SiStripFecCabling
   @author R.Bainbridge
   @brief FEC cabling object for the strip tracker.
*/
class SiStripFecCabling {
  
 public:

  // ----- Constructors, destructors -----
  
  /** */
  SiStripFecCabling( const SiStripFedCabling& );

  /** */
  SiStripFecCabling() {;}
  
  /** */
  ~SiStripFecCabling() {;} //@@ needs implementation!!
  
  /** */
  void buildFecCabling( const SiStripFedCabling& ); 
  
  // ----- Getters -----
  
  /** */
  inline const std::vector<SiStripFecCrate>& crates() const;
  
  /** TEMPORARY method to maintain backward compatibility! */
  inline const std::vector<SiStripFec>& fecs() const;

  /** */
  void connections( std::vector<FedChannelConnection>& ) const;
  
  /** */
  const SiStripModule& module( const FedChannelConnection& conn ) const;

  /** */
  const SiStripModule& module( const uint32_t& dcu_id ) const;
  
  // ----- Setters -----

  /** */
  void addDevices( const FedChannelConnection& conn );

  /** */
  inline void dcuId( const FedChannelConnection& conn );

  /** */
  inline void detId( const FedChannelConnection& conn );

  /** */
  inline void nApvPairs( const FedChannelConnection& conn );
  
  // ----- Misc -----

  /** */
  const NumberOfDevices& countDevices() const;
  
 private:

  /** */
  std::vector<SiStripFecCrate> crates_;
  
};

// ---------- inline methods ----------

const std::vector<SiStripFecCrate>& SiStripFecCabling::crates() const { return crates_; }

// TEMPORARY method to maintain backward compatibility!
const std::vector<SiStripFec>& SiStripFecCabling::fecs() const { 
  static std::vector<SiStripFec> my_fecs;
  if ( !crates_.empty() ) { return crates_[0].fecs(); }
  else { return my_fecs; }
}

void SiStripFecCabling::dcuId( const FedChannelConnection& conn ) { 
  const_cast<SiStripModule&>(module(conn)).dcuId(conn.dcuId()); 
}

void SiStripFecCabling::detId( const FedChannelConnection& conn ) { 
  const_cast<SiStripModule&>(module(conn)).detId(conn.detId()); 
}

void SiStripFecCabling::nApvPairs( const FedChannelConnection& conn ) { 
  const_cast<SiStripModule&>(module(conn)).nApvPairs(conn.nApvPairs()); 
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

#include <sstream>

/** 
    @class NumberOfDevices
    @author R.Bainbridge
    @brief Simple container class for counting devices.
*/
class NumberOfDevices {
  
 public:
  
  NumberOfDevices() { clear(); }
  
  void clear();
  void print( std::stringstream& );
  
 public: // ----- Public member data -----
  
  uint32_t nFecCrates_, nFecSlots_, nFecRings_;      // FECs and rings
  uint32_t nCcuAddrs_, nCcuChans_, nApvs_, nDcuIds_; // CCUs and modules
  uint32_t nDetIds_, nApvPairs_;                     // Geometry
  uint32_t nFedIds_, nFedChans_;                     // FED
  uint32_t nDcus_, nMuxes_, nPlls_, nLlds_;          // Ancilliary devices

}; 

#endif // CalibTracker_SiStripObjects_SiStripFecCabling_H













//inline void fedCh( const FedChannelConnection& conn ); //@@ needs to be implemented

/* void SiStripFecCabling::fedCh( const FedChannelConnection& conn ) {  */
/*   module(conn).detId(conn.fedId());  */
/*   module(conn).detId(conn.fedCh());  */
/* } */


