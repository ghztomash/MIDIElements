// MIDI Elements LED class
// Library to simplify handling of components for MIDI controllers
// Created by Tomash Ghz
// www.tomashg.com
// ghz.tomash@gmail.com

#ifndef RGBLed_H
#define RGBLed_H

//-----------------------------------------------------------------------------------
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#elif defined(WIRING)
#include "Wiring.h"
#else
#include "WProgram.h"
#include "pins_arduino.h"
#endif

/*! \brief Class for handling tri color LEDs.

Enable PWM, to set the brightness through velocity or CC, must be on PWM pin and there will be no ability to change colors through velocity values.
Default color will be active if velocity 127 is recieved. For any other values colours will cycle through.
Intensity will change the PWM write value for different colors.
 */
class RGBLed {
private:
	byte pinA; // pin on teensy
	byte pinB; // pin on teensy for second color
	byte pinC; // pin on teensy for third color
	byte channel; // midi channel
	byte number; // midi number
	byte red;
	byte green;
	byte blue;
	byte intensity; // intensity value for pwm
	bool pwm;
	byte state;
public:
	RGBLed(byte pa, byte pb, byte pc); //!< constructor with pin number for red, green and blue. @param pa red led pin number @param pb green led pin number @param pc blue led pin number
	RGBLed(byte pa, byte pb, byte pc, byte c, byte n); //!< constructor with pin number for red, green, blue, midi channel and midi note. @param pa red led pin number @param pb green led pin number @param pc blue led pin number @param c midi channel @param n midi note or cc number
	RGBLed(byte pa, byte pb, byte pc, byte c, byte n, bool a); //!< constructor with pin number for red, green, blue, midi channel, midi note and PWM. @param pa red led pin number @param pb green led pin number @param pc blue led pin number @param c midi channel @param n midi note or cc number @param a enable PWM
	~RGBLed(); // destructor
	void setOn(byte c, byte n, byte v); //!< read the values for note on and cc and update the led state. if the passed channel and number match the the led state is set to v @param c channel from callback function @param n note or cc number from callback function @param v value or velocity from callback function
	void setOff(byte c, byte n, byte v); //!< read the values for note off and update the led state. @param c channel from callback function @param n note or cc number from callback function @param v value or velocity from callback function
	void setOnSilent(byte c, byte n, byte v); //!< read the values for note on and cc, but do not update the led state. (used for banked LEDs). @param c channel from callback function @param n note or cc number from callback function @param v value or velocity from callback function
	void setOffSilent(byte c, byte n, byte v); //!< read the values for note off, but do not update the led state. @param c channel from callback function @param n note or cc number from callback function @param v value or velocity from callback function
	void set(byte s); //!< manually set the state, but does not update the LED. @param s target state
	void set();  //!< manually update the LED to the set state (used for banked LEDs)
	void setColor(byte r, byte g, byte b, byte i); //!< set the default on color manually. this color will be enabled if the value 127 is received. @param r amount of red color @param g amount of green color @param b amount of blue color @param i intensity amount for the non default colors
};
//-----------------------------------------------------------------------------------

#endif
