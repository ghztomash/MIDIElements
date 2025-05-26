
// Please read MIDIBounce.h for information about the liscence and authors

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#elif defined(WIRING)
#include "Wiring.h"
#else
#include "WProgram.h"
#include "pins_arduino.h"
#endif

#include "MIDIBounce.h"


MIDIBounce::MIDIBounce(uint8_t pin,unsigned long interval_millis)
{
	interval(interval_millis);
	previous_millis = millis();
	state = digitalRead(pin);
    this->pin = pin;
}


void MIDIBounce::write(int new_state)
       {
       	this->state = new_state;
       	digitalWrite(pin,state);
       }


void MIDIBounce::interval(unsigned long interval_millis)
{
  this->interval_millis = interval_millis;
  this->rebounce_millis = 0;
}

void MIDIBounce::rebounce(unsigned long interval)
{
	 this->rebounce_millis = interval;
}



int MIDIBounce::update()
{
	if ( debounce() ) {
        rebounce(0);
        return stateChanged = 1;
    }

     // We need to rebounce, so simulate a state change
     
	if ( rebounce_millis && (millis() - previous_millis >= rebounce_millis) ) {
        previous_millis = millis();
		 rebounce(0);
		 return stateChanged = 1;
	}

	return stateChanged = 0;
}


unsigned long MIDIBounce::duration()
{
  return millis() - previous_millis;
}


int MIDIBounce::read()
{
	return (int)state;
}


// Protected: debounces the pin
int MIDIBounce::debounce() {
	
	uint8_t newState = digitalRead(pin);
	if (state != newState ) {
  		if (millis() - previous_millis >= interval_millis) {
  			previous_millis = millis();
  			state = newState;
  			return 1;
	}
  }
  
  return 0;
	
}

// The risingEdge method is true for one scan after the de-bounced input goes from off-to-on.
bool  MIDIBounce::risingEdge() { return stateChanged && state; }
// The fallingEdge  method it true for one scan after the de-bounced input goes from on-to-off. 
bool  MIDIBounce::fallingEdge() { return stateChanged && !state; }

