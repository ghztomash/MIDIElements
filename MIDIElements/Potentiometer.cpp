// MIDI Elements Potentiometer class
// Library to simplifly handling of compontents for MIDI controllers
// Created by Tomash Ghz
// www.tomashg.com
// ghz.tomash@gmail.com

#include "Potentiometer.h"

//-----------------------------------------------------------------------------------
// constructor
Potentiometer::Potentiometer(byte p){
	Potentiometer(p,0,0,false,true);
}

Potentiometer::Potentiometer(byte p, byte c, byte n){
	Potentiometer(p,c,n,false,false);
}

Potentiometer::Potentiometer(byte p, byte c, byte n, bool sec){
	Potentiometer(p,c,n,sec,false);
}

Potentiometer::Potentiometer(byte p, byte c, byte n, bool sec, bool debug){ // pin, number, channel
	pin=p;
	number=n;
	channel=c;
	secondary=sec;
	debugging=debug;	
}

// destructor
Potentiometer::~Potentiometer(){
	
}

// read
void Potentiometer::read(){
	tempRead=map(analogRead(pin), 0, 1023, 0, 127);
	if (tempRead!=lastValue) { //value changed
      midiCC(tempRead, lastValue);
    }
	lastValue=tempRead;
}

// read value
int Potentiometer::readValue(bool &changed){
	tempRead=map(analogRead(pin), 0, 1023, 0, 127);
    changed=tempRead!=lastValue; //value changed
	lastValue=tempRead;
	return tempRead;
}

// function to handle cc outgoing messages
void Potentiometer::midiCC(int v, int oldv) {
  if (debugging) {//debbuging enabled
    Serial.print("Potentiometer ");
    Serial.print(number);
    Serial.print(" changed value to ");
    Serial.println(v);
  }
  else {
    usbMIDI.sendControlChange(number, v, channel);

    //send the secondary midi messages

    // 0  3            64           124 127
    // |--|-------------|-------------|--| - full range
    //
    // |0=============================127| - CC A
    // |__|on____________________________| - note A
    // |off___________________________|on| - note B
    //    3                          124

    if (secondary) {

      if ((v>3)&&(oldv<=3)) { // send the 0 value note on
        usbMIDI.sendNoteOn(number, 127, channel+1);
      }
      else if ((v<=3)&&(oldv>3)) {
        usbMIDI.sendNoteOff(number, 127, channel+1);
      }
      if ((v>124)&&(oldv<=124)) { // send the 127 value note on
        usbMIDI.sendNoteOn(number+1, 127, channel+1);
      }
      else if ((v<=124)&&(oldv>124)) {
        usbMIDI.sendNoteOff(number+1, 127, channel+1);
      }
    }
  }
}
//-----------------------------------------------------------------------------------