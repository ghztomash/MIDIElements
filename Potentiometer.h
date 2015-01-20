// MIDI Elements Potentiometer class
// Library to simplify handling of components for MIDI controllers
// Created by Tomash Ghz
// www.tomashg.com
// ghz.tomash@gmail.com

#ifndef Potentiometer_H
#define Potentiometer_H

//-----------------------------------------------------------------------------------
#include "WProgram.h" //It is very important to remember this! note that if you are using Arduino 1.0 IDE, change "WProgram.h" to "Arduino.h"

/*! \brief Class for handling faders, knobs or other analog input.

Debugging will enable output to the serial instead of MIDI
Secondary will send a super knob secondary CC message
Mapped values will be constrained and normalized to the min and max values
 */
class Potentiometer {
private:
	bool debugging; // is debugging on
	bool secondary; // send secondary midi signal
	bool mapped;
	int inMin, inMax;
	int lastValue;
	int tempRead;
  int newCC;
	int readValues[3];
	byte pin; // pin on teensy
	byte channel; // midi channel
	byte number; // midi number
	void midiCC(int v, int oldv);
public:
	Potentiometer(byte p); //!< constructor with pin number. @param p analog pin number
	Potentiometer(byte p, byte c, byte n); //!< constructor with pin number, midi channel and cc number . @param p pin number @param c midi channel @param n cc number
	Potentiometer(byte p, byte c, byte n, bool sec); //!< constructor with pin number, midi channel, cc number and secondary super knob. @param p pin number @param c midi channel @param n cc number @param sec enable super knob
	Potentiometer(byte p, byte c, byte n, bool sec, bool debug); //!< constructor with pin number, midi channel, cc number, secondary super knob and debugging. @param p pin number @param c midi channel @param n cc number @param sec enable super knob @param debug enable debugging
	~Potentiometer(); // destructor
	void read(); //!< read the values and send a midi message if the fader or knob state changed. use in main loop
	void readAvr(); //!< read the values for couple of iterations for a smoother value and send a midi message if the fader or knob state changed. use in main loop
	int readValue(bool &changed); //!<  read and return the analog value, pass state change @param changed will beset to true if the state of the value changed from last time
	int readValueAvr(bool &changed); //!<  read and return a smooth analog value, pass state change @param changed will beset to true if the state of the value changed from last time
	void changeSecondary(bool s); //!< enable or disable the secondary super knob cc messages @param s enable super knob
	void bound(int iMin, int iMax); //!< map and bound the analog readings to minimum and maximum values, useful for normalizing light or force sensors. @param iMin the value below everything will be set as 0 @param iMax the value above everything will be set as 127
};
//-----------------------------------------------------------------------------------

#endif
