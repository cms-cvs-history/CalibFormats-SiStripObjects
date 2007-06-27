 // -*- C++ -*-
//
// Package:     SiStripObjects
// Class  :     SiStripGain
// Implementation:
//     <Notes on implementation>
// Original Author:  gbruno
//         Created:  Wed Mar 22 12:24:33 CET 2006
// $Id: SiStripGain.cc,v 1.1 2007/05/02 12:33:45 gbruno Exp $

#include "FWCore/Framework/interface/eventsetupdata_registration_macro.h"
#include "CalibFormats/SiStripObjects/interface/SiStripGain.h"
//#include "FWCore/MessageLogger/interface/MessageLogger.h"

using namespace std;


SiStripGain::SiStripGain()
{
}



SiStripGain::~SiStripGain()
{
}


SiStripGain::SiStripGain(const SiStripApvGain& apvgain, double factor) : apvgain_(&apvgain), norm_(factor)
{

}

float SiStripGain::getStripGain(const uint16_t& strip, const SiStripApvGain::Range& range) const{

  return (apvgain_->getStripGain(strip,range))/norm_;

}
float SiStripGain::getApvGain(const uint16_t& apv, const SiStripApvGain::Range& range) const {

  return (apvgain_->getApvGain(apv,range))/norm_;

}


void SiStripGain::getDetIds(std::vector<uint32_t>& DetIds_) const {

  return apvgain_->getDetIds(DetIds_);

}

const SiStripApvGain::Range SiStripGain::getRange(const uint32_t& DetId) const {
  return apvgain_->getRange(DetId);

}



EVENTSETUP_DATA_REG(SiStripGain);