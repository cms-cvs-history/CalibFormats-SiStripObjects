#ifndef SiStripObjects_SiStripQuality_h
#define SiStripObjects_SiStripQuality_h
// -*- C++ -*-
// -*- C++ -*-
//
// Package:     SiStripObjects
// Class  :     SiStripQuality
//
/**\class SiStripQuality SiStripQuality.h SiStripQuality.cc

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Domenico Giordano
// Created:     Wed Sep 26 17:42:12 CEST 2007
// $Id: SiStripQuality.h,v 1.3 2007/10/18 08:42:17 giordano Exp $
//


#include "CondFormats/SiStripObjects/interface/SiStripBadStrip.h"
#include "FWCore/ParameterSet/interface/FileInPath.h"
#include "CalibTracker/SiStripCommon/interface/SiStripDetInfoFileReader.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include <vector>

class SiStripQuality: public SiStripBadStrip {

 public:

  struct BadComponent{
    uint32_t detid;
    unsigned short BadApvs : 6;
    unsigned short BadFibers :3;
    bool BadModule :1;
  };

  class BadComponentStrictWeakOrdering{
  public:
    bool operator() (const BadComponent& p,const uint32_t i) const {return p.detid < i;}
  };
  
  SiStripQuality(); //takes default file for SiStripDetInfoFileReader
  SiStripQuality(edm::FileInPath&);
  SiStripQuality(const SiStripQuality&); //copy constructor

  ~SiStripQuality(){ 
    LogTrace("SiStripQuality") << "SiStripQuality destructor" << std::endl; 
    delete reader;
  }

  void clear(){
    v_badstrips.clear();
    indexes.clear();
    BadComponentVect.clear();
    toCleanUp=false;
  }

  void add(const SiStripBadStrip*);
 
  bool cleanUp();

  void fillBadComponents();

  SiStripQuality& operator +=(const SiStripQuality&); 
  SiStripQuality& operator -=(const SiStripQuality&);
  const SiStripQuality operator -(const SiStripQuality&) const ;
  bool operator ==(const SiStripQuality&) const;
  bool operator !=(const SiStripQuality&) const;
  
  edm::FileInPath getFileInPath() const {return FileInPath_;}

  //------- Interface for the user ----------//

  bool IsModuleBad(const uint32_t& detid) const;
  bool IsFiberBad(const uint32_t& detid, const short& fiberNb) const;
  bool IsApvBad(const uint32_t& detid, const short& apvNb) const;
  bool IsStripBad(const uint32_t& detid, const short& strip) const;
  
  short getBadApvs(const uint32_t& detid) const; 
  //each bad apv correspond to a bit to 1: num=
  //0 <-> all good apvs
  //1 <-> only apv 0 bad
  //2<-> only apv 1 bad
  //3<->  apv 0 and 1 bad
  // 4 <-> only apv 2 bad
  //...
  short getBadFibers(const uint32_t& detid) const; 
  //each bad fiber correspond to a bit to 1: num=
  //0 <-> all good fibers
  //1 <-> only fiber 0 bad
  //2<-> only fiber 1 bad
  //3<->  fiber 0 and 1 bad
  // 4 <-> only fiber 2 bad
  //...
  
  const std::vector<BadComponent>& getBadComponentList() const { return BadComponentVect; }   

  void compact(unsigned int&,std::vector<unsigned int>&);

 private:

  void compact(std::vector<unsigned int>&,std::vector<unsigned int>&,unsigned short&);
  void subtract(std::vector<unsigned int>&,const std::vector<unsigned int>&);
  void subtraction(std::vector<unsigned int>&,const unsigned int&);
  bool put_replace(const uint32_t& DetId, Range input);

  bool toCleanUp;
  edm::FileInPath FileInPath_;
  SiStripDetInfoFileReader* reader;

  std::vector<BadComponent> BadComponentVect;
};

#endif