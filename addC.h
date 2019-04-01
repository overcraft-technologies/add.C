/*
  addC.h - Library for using the "addC" USB Type-C module.	
  The library uses the Arduino Wire.h library to communicate with the TUSB320 chip. 
  Created by Alexander J. Dick, OverCraft Technologies, March 29th, 2019.
  Released into the public domain.
*/
#ifndef addC_h
#define addC_h

#include "Arduino.h"
#include "Wire.h"

class addC
{
  public:
    addC(int address, bool noDefault);
    int deviceId(int addr);
    void currentAdvertise(int currentMode);
	int currentDetect();
	int accessoryConnected();
	bool activeCable();
	
	int attachedState();
	bool cableDirection();
	bool interruptStatus();
	void interruptClear();
	int drpDutyCycle();
	
	void debounce(int debounce);
	void modeSet(int mode);
	int val;
	
	
  private:
    int _address;
	bool _noDefault;
	int _addr;
	int _currentMode;
	int _debounce;
	int _mode;
	int _val;
	
	
};

#endif