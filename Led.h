// MIDI Elements LED class
// Library to simplify handling of components for MIDI controllers
// Created by Tomash Ghz
// www.tomashg.com
// ghz.tomash@gmail.com

#ifndef Led_H
#define Led_H

//-----------------------------------------------------------------------------------
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#elif defined(WIRING)
#include "Wiring.h"
#else
#include "WProgram.h"
#include "pins_arduino.h"
#endif

/*! \brief Class for handling single color LEDs.

Enable PWM, to set the brightness through velocity or CC, must be on PWM pin.
 */
class Led {
private:
	byte pin; //!< pin on teensy
	byte channel; //!< midi channel
	byte number; //!< midi number
	bool pwm; //!< pwm, if enabled it is possible to set the brightness through velocity or cc, must be on pwm pin
	bool state; //!< led state
public:
	Led(byte p); //!< constructor with pin number. @param p pin number
	Led(byte p, byte c, byte n); //!< constructor with pin number, midi channel and midi note. @param p pin number @param c midi channel @param n cc number or note
	Led(byte p, byte c, byte n, bool a); //!< constructor with pin number, midi channel, midi note and pwm. @param p pin number @param c midi channel @param n cc number or note @param a enable PWM
	~Led(); // destructor
	void setOn(byte c, byte n, byte v); //!< read the values for note on and cc and update the led state. if the passed channel and number match the the led state is set to v @param c channel from callback function @param n note or cc number from callback function @param v value or velocity from callback function
	void setOff(byte c, byte n, byte v); //!< read the values for note off and update the led state. @param c channel from callback function @param n note or cc number from callback function @param v value or velocity from callback function
	void setOnSilent(byte c, byte n, byte v); //!< read the values for note on and cc, but do not update the led state. (used for banked LEDs). @param c channel from callback function @param n note or cc number from callback function @param v value or velocity from callback function
	void setOffSilent(byte c, byte n, byte v); //!< read the values for note off, but do not update the led state. @param c channel from callback function @param n note or cc number from callback function @param v value or velocity from callback function
	void set(bool s); //!< manually set the state, but does not update the LED. @param s target state
	void set(); //!< manually update the LED to the set state (used for banked LEDs)
};
//-----------------------------------------------------------------------------------

#endif
