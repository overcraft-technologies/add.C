/*
  addC.h - Library for using the "addC" USB Type-C module.	
  The library uses the Arduino Wire.h library to communicate with the TUSB320 chip. 
  Created by Alexander J. Dick, OverCraft Technologies, March 29th, 2019.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Wire.h"
#include "addC.h"

addC::addC(int address, bool noDefault) 	//setup
{
	_address = address;
	_noDefault = noDefault;
	
	
	Wire.begin();
}

int addC::deviceId(int addr)
{
	_addr = addr;							//Secure Variable
	
	Wire.beginTransmission(_address);		//Access Register
	Wire.write(addr);
	Wire.endTransmission();
	
	Wire.requestFrom(_address, 1);			//Request Register
	
	while(Wire.available() != 1) {;}		//Read Register
	_val = Wire.read();
	return _val;							//Return _value
}

void addC::currentAdvertise(int currentMode)
{
	_currentMode = currentMode << 6;		//Bitshift-Correction
	
	Wire.beginTransmission(_address);		//Access Register
	Wire.write(8);
	Wire.endTransmission();
	
	Wire.requestFrom(_address, 1);			//Request Register
	
	while(Wire.available() != 1) {;}		//Read Register
	_val =  Wire.read();
	
	_val = _val & B00111111;				//Reset Current_Mode_Advertise Bits
	
	Wire.beginTransmission(_address);
	Wire.write(8);
	Wire.write(_val | _currentMode);		//Write Register/Bits
	Wire.endTransmission();
}

int addC::currentDetect()
{
	Wire.beginTransmission(_address);		//Access Register
	Wire.write(8);
	Wire.endTransmission();
	
	Wire.requestFrom(_address, 1);			//Request Register
	
	while(Wire.available() != 1) {;}		//Read Register
	_val =  Wire.read();
	
	_val = _val & B00110000;				//Exclude Current_Mode_Detect Bits
	_val = _val >> 4;						//Bitshift-Correction
	
	return _val;							//Return _value
}

int addC::accessoryConnected()
{
	Wire.beginTransmission(_address);		//Access Register
	Wire.write(8);
	Wire.endTransmission();
	
	Wire.requestFrom(_address, 1);			//Request Register
	
	while(Wire.available() != 1) {;}		//Read Register
	_val =  Wire.read();
	
	_val = _val & B00001110;				//Exclude Accessory_Connected Bits
	_val = _val >> 1;						//Bitshift-Correction
	
	return _val;							//Return _value
}

bool addC::activeCable()
{
	Wire.beginTransmission(_address);		//Access Register
	Wire.write(8);
	Wire.endTransmission();
	
	Wire.requestFrom(_address, 1);			//Request Register
	
	while(Wire.available() != 1) {;}		//Read Register
	_val =  Wire.read();
	
	_val = _val & B00000001;				//Exclude Current_Mode_Detect Bits
	
	return _val;							//Return _value
}

int addC::attachedState()
{
	Wire.beginTransmission(_address);		//Access Register
	Wire.write(9);
	Wire.endTransmission();
	
	Wire.requestFrom(_address, 1);			//Request Register
	
	while(Wire.available() != 1) {;}		//Read Register
	_val =  Wire.read();
	
	_val = _val & B11000000;				//Exclude Attached_State Bits
	_val = _val >> 6;						//Bitshift-Correction
	
	return _val;							//Return _value
}

bool addC::cableDirection()
{
	Wire.beginTransmission(_address);		//Access Register
	Wire.write(9);
	Wire.endTransmission();
	
	Wire.requestFrom(_address, 1);			//Request Register
	
	while(Wire.available() != 1) {;}		//Read Register
	int _val =  Wire.read();
	
	_val = _val & B00100000;				//Exclude Cable_Dir Bits
	_val = _val >> 5;						//Bitshift-Correction
	
	return _val;							//Return _value
}

bool addC::interruptStatus()
{
	Wire.beginTransmission(_address);		//Access Register
	Wire.write(9);
	Wire.endTransmission();
	
	Wire.requestFrom(_address, 1);			//Request Register
		
	while(Wire.available() != 1) {;}		//Read Register
	_val =  Wire.read();
	
	_val = _val & B00010000;				//Exclude Interrupt_Status Bits
	_val = _val >> 4;						//Bitshift-Correction
	
	return _val;							//Return _value
}

void addC::interruptClear()
{
	Wire.beginTransmission(_address);		//Access Register
	Wire.write(9);
	Wire.endTransmission();
	
	Wire.requestFrom(_address, 1);			//Request Register
	
	while(Wire.available() != 1) {;}		//Read Register
	_val =  Wire.read();
	
	_val = _val & B11101111;				//Reset Current_Mode_Advertise Bits
	
	Wire.beginTransmission(_address);
	Wire.write(9);
	Wire.write(_val);						//Write Register/Bits
	Wire.endTransmission();
}

int addC::drpDutyCycle()
{
	Wire.beginTransmission(_address);		//Access Register
	Wire.write(9);
	Wire.endTransmission();
	
	Wire.requestFrom(_address, 1);			//Request Register
	
	while(Wire.available() != 1) {;}		//Read Register
	_val =  Wire.read();
	
	_val = _val & B00000110;				//Exclude DRP_Duty_Cycle Bits
	_val = _val >> 1;						//Bitshift-Correction
	
	return _val;							//Return _value
}


void addC::debounce(int debounce)
{
	_debounce = debounce << 6;				//Bitshift-Correction
	
	Wire.beginTransmission(_address);		//Access Register
	Wire.write(10);
	Wire.endTransmission();
	
	Wire.requestFrom(_address, 1);			//Request Register
	
	while(Wire.available() != 1) {;}		//Read Register
	_val =  Wire.read();
	
	_val = _val & B00111111;				//Reset Debounce Bits
	
	Wire.beginTransmission(_address);
	Wire.write(10);
	Wire.write(_val | _debounce);			//Write Register/Bits
	Wire.endTransmission();
}

void addC::modeSet(int mode)
{
	_mode = mode << 4;						//Bitshift-Correction
	
	Wire.beginTransmission(_address);		//Access Register
	Wire.write(10);
	Wire.endTransmission();
	
	Wire.requestFrom(_address, 1);			//Request Register
	
	while(Wire.available() != 1) {;}		//Read Register
	_val =  Wire.read();
	
	_val = _val & B11001111;				//Reset Current_Mode_Advertise Bits
	
	Wire.beginTransmission(_address);
	Wire.write(10);
	Wire.write(_val | _mode);				//Write Register/Bits
	Wire.endTransmission();
}
