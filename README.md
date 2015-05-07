# MiniKing - MiniKing Sonar Library

This package contains a C++ class for programming the MiniKing sonar, from Tritech. It is released as a ROS package, and relies on Boost for serial communication. Perhaps this library can be also used with other devices that implement the SeaNet protocol, but it has only validated used with the MiniKing model.

This library was implemented during the development of my Master's Thesis and it can be considered as research code. The authors are not responsible for any errors it may contain. Use it at your own risk!

[![Build Status](https://travis-ci.org/srv/libminiking.svg?branch=master)](https://travis-ci.org/srv/libminiking)


## Related publication

The architecture of the library is detailed in:

**Implantación de un Sensor Sónar para el Control de la Navegación de un Vehículo Submarino**     
Emilio Garcia-Fidalgo     
Supervised by: Alberto Ortiz and Javier Antich     
Master's Thesis     
University of the Balearic Islands, Spain, 2007

The document can be downloaded from [here] (http://emiliofidalgo.github.io/static/papers/mthesis_Garcia2007.pdf) (Spanish). If you use this software in an academic work, please cite:

    @MASTERSTHESIS{GarciaFidalgo2007,
        author = {Emilio Garcia-Fidalgo},
        title = {{Implantaci\'on de un Sensor S\'onar para el Control de la Navegaci\'on de un Veh\'iculo Submarino}},
        school = {University of the Balearic Islands},
        address = {Spain},
        year = {2007}
    }
    
## Conditions of use

The library is distributed under the terms of the [BSD License] (http://github.com/emiliofidalgo/miniking/blob/master/LICENSE).

## Installation

1. First of all, you will need to have installed all library dependencies:

	`sudo apt-get install libboost-system-dev`     

2. Clone the repository into your workspace:
	
	`cd ~/your_workspace/src`   
	`git clone https://github.com/emiliofidalgo/miniking.git`   

3. Compile the package using `catkin_make`:
	
	`cd ..`   
	`catkin_make -DCMAKE_BUILD_TYPE=Release`   

4. Include the headers and link the library in your `CMakeList.txt` to use it.

## Quick Tutorial

By default, the sonar is configured with the following parameters:
- Imaging Sonar
- Frequency: 675 Khz
- Range Scale: 30 Metres
- Scan Limits: Left = 0 ; Right = 0 (in gradians)
- ADSpan = 12 Db
- ADLow = 13 Db
- Initial Gain: 40%
- Resolution: Medium
- Bins: 300
- 8 Data Bits
- Scan continuous
- Clockwise
- Normal mounted
- Motor Enabled
- Transmitter Enabled
- Only One Channel Operation
- Sonar has scanning motor
- Do not apply offsets
- Not pingpong, only one channel
- Do not stare in a fixed direction
- Do not ignore sensor

First of all, you need to instantiate a MiniKing object at `/dev/ttyS0`, using timeout = 0:

    MiniKing mk("/dev/ttyS0", 0);

Next, it is necessary to call the `initSonar` method to initialize the communication between the sonar and the computer:

    sn.initSonar();
    
After that, the sonar configuration can be modified according to your needs. Make all changes that you want and, then, resend the configuration to the sonar using the `updateConfig` method. Example:

    sn.setRange(25);
    sn.setBins(200);
    sn.setContinuous(false);
    sn.setLeftLim(90);
    sn.setRightLim(180);
    sn.updateConfig();
 
 To restart the device, call to the following method:
 
    sn.reboot();
    
After this operation, the parameters are reset to the default ones. It is not needed to call to `updateConfig` in this case.

In order to get data from the sonar, use the `getScanLine` method. Here is an example for this:

    BYTE *data = sn.getScanLine();
 
    printf("SCAN POSITION IN DEGREES: %.2f\n", sn.getPosition());
    for (int i = 0; i < sn.getDataLength(); i++)
        printf("%d ", data[i]);* 

## Contact

If you have problems or questions using the library, please contact the authors (emilio.garcia@uib.es). Improvements are totally welcome.
