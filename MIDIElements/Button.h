// MIDI Elements Button class
// Library to simplifly handling of compontents for MIDI controllers
// Created by Tomash Ghz
// www.tomashg.com
// ghz.tomash@gmail.com

#ifndef Button_H
#define Button_H

//-----------------------------------------------------------------------------------
#include "WProgram.h" //It is very important to remember this! note that if you are using Arduino 1.0 IDE, change "WProgram.h" to "Arduino.h"
#include <MIDIBounce.h>

class Button {
private:
	MIDIBounce *bButn; // bounce class button
	bool debugging; // is debugging on
	bool secondary; // send secondary midi signal
	byte pin; // pin on teensy
	byte channel; // midi channel
	byte number; // midi number
	byte velocity; // midi velocity
	void noteOnOff(bool v); // send note on off
public:
	Button(byte p); // constructors
	Button(byte p, byte c, byte n);
	Button(byte p, byte c, byte n, bool sec);
	Button(byte p, byte c, byte n, bool sec, bool debug);
	~Button(); // destructor
	void read(); // read the values
	bool readValue(bool &changed); // read the values and return if the button is high, and pass statechange
	void setVelocity(byte v); // change the note on velocity value
};
//-----------------------------------------------------------------------------------

#endif