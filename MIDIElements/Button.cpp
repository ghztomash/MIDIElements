// MIDI Elements button class
// Library to simplifly handling of compontents for MIDI controllers
// Created by Tomash Ghz
// www.tomashg.com
// ghz.tomash@gmail.com

#include "Button.h"

//-----------------------------------------------------------------------------------
// constructor
Button::Button(byte p){
	Button(p,0,0,false,true);
}

Button::Button(byte p, byte c, byte n){
	Button(p,c,n,false,false);
}

Button::Button(byte p, byte c, byte n, bool sec){
	Button(p,c,n,sec,false);
}

Button::Button(byte p, byte c, byte n, bool sec, bool debug){ // pin, number, channel
	pin=p;
	number=n;
	channel=c;
	secondary=sec;
	debugging=debug;
	velocity=127;
	
	pinMode(pin, INPUT_PULLUP); // enable the pin for input
		
	bButn = new Bounce(pin, 10); // create new bounce object for pin
}

// destructor
Button::~Button(){
	delete bButn;
}

// read
void Button::read(){
	if (bButn->update()) {//state changed

      if (bButn->read()==LOW) {//is pressed
        noteOnOff(true);
      }
      else {
        noteOnOff(false);
      }
    }
}

// read value
bool Button::readValue(bool &changed){
	changed=bButn->update(); //state changed

      if (bButn->read()==LOW) {//is pressed
        return true;
      }
      else {
        return false;
      }
}

// set note on velocity
void Button::setVelocity(byte v){
	velocity=v;
}

//send midinote on off
void Button::noteOnOff(bool v){
  if(v){
    if (debugging) {//debbuging enabled
      Serial.print("Button ");
      Serial.print(number);
      Serial.println(" pressed.");
    }
	else{ // send midi note
		usbMIDI.sendNoteOn(number, velocity, channel);
		if(secondary)
			usbMIDI.sendControlChange(number, 127, channel);
	}
  }
  else{
	if (debugging) {//debbuging enabled
      Serial.print("Button ");
      Serial.print(number);
      Serial.println(" released.");
    }
	else{
		if(secondary)
			usbMIDI.sendControlChange(number, 0, channel);
		usbMIDI.sendNoteOff(number, 0, channel);
	}
  }
}
//-----------------------------------------------------------------------------------