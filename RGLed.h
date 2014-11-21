// MIDI Elements LED class
// Library to simplify handling of components for MIDI controllers
// Created by Tomash Ghz
// www.tomashg.com
// ghz.tomash@gmail.com

#ifndef RGLed_H
#define RGLed_H

//-----------------------------------------------------------------------------------
#include "WProgram.h" //It is very important to remember this! note that if you are using Arduino 1.0 IDE, change "WProgram.h" to "Arduino.h"

/*! \brief Class for handling bi color LEDs.

Enable PWM, to set the brightness through velocity or CC, must be on PWM pin and there will be no ability to change colors through velocity values.
Default color will be active if velocity 127 is recieved. For any other values colours will cycle through.
Intensity will change the PWM write value for different colors.
 */

class RGLed {
private:
	byte pinA; // pin on teensy
	byte pinB; // pin on teensy for second color
	byte channel; // midi channel
	byte number; // midi number
	byte red;
	byte green;
	byte intensity; // intensity value for pwm
	bool pwm;
	byte state;
public:
	RGLed(byte pa, byte pb); //!< constructor with pin number for red and green. @param pa red led pin number @param pb green led pin number
	RGLed(byte pa, byte pb, byte c, byte n); //!< constructor with pin number for red, green, midi channel and midi note. @param pa red led pin number @param pb green led pin number @param c midi channel @param n midi note or cc number
	RGLed(byte pa, byte pb, byte c, byte n, bool a); //!< constructor with pin number for red, green, midi channel, midi note and pwm. @param pa red led pin number @param pb green led pin number @param c midi channel @param n midi note or cc number @param a enable PWM
	~RGLed(); // destructor
	void setOn(byte c, byte n, byte v); //!< read the values for note on and cc and update the led state. if the passed channel and number match the the led state is set to v @param c channel from callback function @param n note or cc number from callback function @param v value or velocity from callback function
	void setOff(byte c, byte n, byte v); //!< read the values for note off and update the led state. @param c channel from callback function @param n note or cc number from callback function @param v value or velocity from callback function
	void setOnSilent(byte c, byte n, byte v); //!< read the values for note on and cc, but do not update the led state. (used for banked LEDs). @param c channel from callback function @param n note or cc number from callback function @param v value or velocity from callback function
	void setOffSilent(byte c, byte n, byte v); //!< read the values for note off, but do not update the led state. @param c channel from callback function @param n note or cc number from callback function @param v value or velocity from callback function
	void set(byte s); //!< manually set the state, but does not update the LED. @param s target state
	void set(); //!< manually update the LED to the set state (used for banked LEDs)
	void setColor(byte r, byte g, byte i); //!< set the default on color manually. this color will be enabled if the value 127 is received. @param r amount of red color @param g amount of green color @param i intensity amount for the non default colors
};
//-----------------------------------------------------------------------------------

#endif