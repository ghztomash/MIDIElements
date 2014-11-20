// MIDI Elements Button class
// Library to simplify handling of components for MIDI controllers
// Created by Tomash Ghz
// www.tomashg.com
// ghz.tomash@gmail.com

#ifndef Button_H
#define Button_H

//-----------------------------------------------------------------------------------
#include "WProgram.h" //It is very important to remember this! note that if you are using Arduino 1.0 IDE, change "WProgram.h" to "Arduino.h"
#include <MIDIBounce.h>

/*! \brief Class for handling push button switches.

Connect the button to ground and input pin, there is no need for a pull-up resistor, it is enabled internally.
Enable Secondary to send secondary CC messages. (used for mapping momentary switches in Ableton)
Enable debug to print to serial port instead of midi.
 */

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
	Button(byte p); //!< constructor with pin number. @param p pin number
	Button(byte p, byte c, byte n); //!< constructor with pin number, midi channel and midi note. @param p pin number @param c midi channel @param n midi note
	Button(byte p, byte c, byte n, bool sec); //!< constructor with pin number, midi channel, midi note and secondary messages. @param p pin number @param c midi channel @param n midi note @param sec enable secondary messages
	Button(byte p, byte c, byte n, bool sec, bool debug); //!< constructor with pin number, midi channel, midi note, secondary messages and debugging. @param p pin number @param c midi channel @param n midi note @param sec enable secondary message @param debug enable debugging
	~Button(); // destructor
	void read(); //!< read the values and send a midi message if the button state changed. use in main loop
	bool readValue(bool &changed); //!<  read the values and return if the button is pressed, pass state change @param changed will beset to true if the state of the button changed
	void setVelocity(byte v); //!< change the note on velocity value of the outgoing midi message. @param v set velocity value
};
//-----------------------------------------------------------------------------------

#endif