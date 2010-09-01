#include <iostream>
#include <fstream>

#include "LaserScannerConfiguration.h"
#include "SickS300Configuration.h"
#include "LaserScannerData.h"
#include "LaserScannerDataWithIntensities.h"
#include "LaserScanner.h"
#include "SickS300.h"
#include "Errors.h"
#include "Logger.h"



#include <boost/units/systems/si.hpp>
#include <boost/units/make_scaled_unit.hpp>
#include <boost/units/systems/si/prefixes.hpp>




using namespace std;
using namespace boost::units;
using namespace boost::units::si;
using namespace boost::units::angle;







int main(){
/*
  SickLMS2xxConfiguration config;

  config.scan_angle = 2 *radian;
  double test = config.scan_angle.value(); //mm
  config.scan_resolution = 2 *radian;


  std::cout << "min Range: " << config.scan_angle <<std::endl
            << "max Range: " << config.scan_resolution <<std::endl
            << "test: " << test <<std::endl;
*/

// Read logging settings from a file
  //  std::ifstream file("log_settings.ini");
 //   logging::init_from_stream(file);
      // Initialize logging to std::cout
    logging::init_log_to_console(std::cout);
    // Initialize logging to the "test.log" file
    logging::init_log_to_file("log.txt");


// Here we go, we can write logs right away
    src::logger lg;
    BOOST_LOG(lg) << "Hello world!";


  SickS300Configuration config;
  config.devicePath = "/dev/ttyUSB0"; // Device path of the Sick LMS 2xx
  config.baud = BAUD_500K;

  SickS300 scanner;

  Errors errors;

  LaserScannerData scanData;

  if(!scanner.setConfiguration(config, errors))
    return 0;

  if(!scanner.getConfiguration(config, errors))
    return 0;

  if(!scanner.getData(scanData, errors))
    return 0;


  return 0;
}