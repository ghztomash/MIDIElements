// MIDI Elements LED class
// Library to simplifly handling of compontents for MIDI controllers
// Created by Tomash Ghz
// www.tomashg.com
// ghz.tomash@gmail.com

#ifndef RGLed_H
#define RGLed_H

//-----------------------------------------------------------------------------------
#include "WProgram.h" //It is very important to remember this! note that if you are using Arduino 1.0 IDE, change "WProgram.h" to "Arduino.h"

class RGLed {
private:
	byte pinA; // pin on teensy
	byte pinB; // pin on teensy for second color
	byte channel; // midi channel
	byte number; // midi number
	bool pwm;
	byte state;
public:
	RGLed(byte pa, byte pb); // constructors
	RGLed(byte pa, byte pb, byte c, byte n);
	RGLed(byte pa, byte pb, byte c, byte n, bool a);
	~RGLed(); // destructor
	void setOn(byte c, byte n, byte v); // read the values for note on and cc
	void setOff(byte c, byte n, byte v); // read the values for note off
	void setOnSilent(byte c, byte n, byte v); // read the values for note on and cc
	void setOffSilent(byte c, byte n, byte v); // read the values for note off
	void set(byte s); // set led to state
	void set();
};
//-----------------------------------------------------------------------------------

#endif