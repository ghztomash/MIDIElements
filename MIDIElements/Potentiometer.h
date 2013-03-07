// MIDI Elements Potentiometer class
// Library to simplifly handling of compontents for MIDI controllers
// Created by Tomash Ghz
// www.tomashg.com
// ghz.tomash@gmail.com

#ifndef Potentiometer_H
#define Potentiometer_H

//-----------------------------------------------------------------------------------
#include "WProgram.h" //It is very important to remember this! note that if you are using Arduino 1.0 IDE, change "WProgram.h" to "Arduino.h"

class Potentiometer {
private:
	bool debugging; // is debugging on
	bool secondary; // send secondary midi signal
	int lastValue;
	int tempRead;
	byte pin; // pin on teensy
	byte channel; // midi channel
	byte number; // midi number
	void midiCC(int v, int oldv);
public:
	Potentiometer(byte p); // constructors
	Potentiometer(byte p, byte c, byte n);
	Potentiometer(byte p, byte c, byte n, bool sec);
	Potentiometer(byte p, byte c, byte n, bool sec, bool debug);
	~Potentiometer(); // destructor
	void read(); // read the values
	int readValue(bool &changed); // read the values and return if the button is high, and pass statechange
};
//-----------------------------------------------------------------------------------

#endif