#include "CalibFormats/SiStripObjects/interface/SiStripGain.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <sstream>

int test( const bool testBool )
{
  if( testBool ) {
    std::cout << "--- Test PASSED ---" << std::endl;
    std::cout << std::endl;
    return 0;
  }
  std::cout << "--- Test FAILED ---" << std::endl;
  std::cout << std::endl;
  return 1;
}

// The encoding probably causes loss of accuracy in the saved number which
// is way low in the bits. The number shown by a cout is the same, but comparing
// directly the two doubles we see they are not equal. For this reason, and for
// the purpose of testing, multiply them by 1000 and convert them to int before
// comparing them.

bool compare(const double & value1, const double & value2)
{
  return( int(value1*1000) == int(value2*1000) );
}

int main()
{
  int failedTests = 0;

  double inputValue1 = 0.4;
  double inputValue2 = 0.5;

  // Prepare vector of gain values and corresponding range
  std::vector<float> v;
  v.push_back(inputValue1);
  v.push_back(inputValue2);
  SiStripApvGain::Range range1 = make_pair(v.begin(), v.begin()+1);      
  SiStripApvGain::Range range2 = make_pair(v.begin()+1, v.end());      

  std::cout << "Testing the SiStripGain object with a single apvGain" << std::endl;

  SiStripApvGain apvGain1;
  // DetId and range
  apvGain1.put(100, range1);
  apvGain1.put(101, range2);
  SiStripGain gain(apvGain1, 1.);

  std::cout << "After inserting a single gain:" << std::endl;
  std::stringstream ss;
  gain.printDebug(ss);
  std::cout << ss.str() << std::endl;

  double gainValue = gain.getApvGain(0, range1);
  std::cout << "Input value = " << inputValue1 << "; gain value = " << gainValue << std::endl;
  // std::cout << "gainValue("<<gainValue<<") == inputValue1("<<inputValue1<<") = " << compare(inputValue1, gainValue) << std::endl;
  failedTests += test( compare(inputValue1, gainValue) );
  gainValue = gain.getApvGain(0, range2);
  std::cout << "Input value = " << inputValue2 << "; gain value = " << gainValue << std::endl;
  // std::cout << "gainValue("<<gainValue<<") == inputValue2("<<inputValue2<<") = " << compare(inputValue2, gainValue) << std::endl;
  failedTests += test( compare(inputValue2, gainValue) );

  // Adding a second gain
  // --------------------
  std::vector<float> v2;
  v2.push_back(inputValue2);
  v2.push_back(inputValue1);
  SiStripApvGain::Range range21 = make_pair(v2.begin(), v2.begin()+1);      
  SiStripApvGain::Range range22 = make_pair(v2.begin()+1, v2.end());      

  SiStripApvGain apvGain2;
  // DetId and range
  apvGain2.put(100, range21);
  apvGain2.put(101, range22);

  gain.multiply(apvGain2, 1.);

  std::cout << "After inserting a second gain:" << std::endl;
  ss.str("");
  gain.printDebug(ss);
  std::cout << ss.str() << std::endl;

  std::vector<SiStripApvGain::Range> rangeVector1 = gain.getAllRanges(100);
  gainValue = gain.getApvGain(0, rangeVector1);
  std::cout << "Input values = " << inputValue1 << ", " << inputValue2 << "; gain value = " << gainValue << std::endl;
  failedTests += test( compare(inputValue1*inputValue2, gainValue) );
  // SiStripApvGain::Range rangeToInspect2 = gain.getRange(101);
  std::vector<SiStripApvGain::Range> rangeVector2 = gain.getAllRanges(101);
  gainValue = gain.getApvGain(0, rangeVector1);
  std::cout << "Input values = " << inputValue2 << ", " << inputValue1 << "; gain value = " << gainValue << std::endl;
  failedTests += test( compare(inputValue2*inputValue1, gainValue) );

  std::cout << "Failed tests = " << failedTests << std::endl;

  return 0;
}
