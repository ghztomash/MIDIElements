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
	mapped=false;
}

// destructor
Potentiometer::~Potentiometer(){
	
}

// read
void Potentiometer::read(){

	if(mapped){
			tempRead=constrain(analogRead(pin),inMin,inMax);

      /* Need to maintain analog resolution for the next 
         'if' statement but leaving out the upper and
         lower limits prevents messages outside the MIDI range*/
			tempRead=map(tempRead,inMin,inMax,7,1015);
		}
	else
    tempRead=analogRead(pin);

  /*1 - Split the analog signal into blocks of 4
        and every other block of four is ignored.
    2 - Reduce the resolution for MIDI and compare
        against the previously sent message.*/
  if ((tempRead/4)%2 == 0 && tempRead/8 != lastValue){
    newCC = tempRead/8;
    midiCC(newCC, lastValue);
    lastValue = newCC;
  }
}

// read
void Potentiometer::readAvr(){
	tempRead=0;
	for(int i=0; i<10; i++){
		tempRead+=analogRead(pin);
	}
	tempRead=tempRead/10;
	
	if(mapped)
	{
		tempRead=map(constrain(tempRead,inMin,inMax),inMin,inMax,0,127);
		}
	else
		tempRead=map(tempRead, 0, 1023, 0, 127);
	
	if (tempRead!=lastValue) { //value changed
      midiCC(tempRead, lastValue);
    }
	
	lastValue=tempRead;
}

// enable maped values
void Potentiometer::bound(int iMin, int iMax){
	mapped=true;
	
	inMin=iMin;
	inMax=iMax;
}

// read value
int Potentiometer::readValue(bool &changed){
	tempRead=map(analogRead(pin), 0, 1023, 0, 127);
    changed=tempRead!=lastValue; //value changed
	lastValue=tempRead;
	return tempRead;
}

// read value
int Potentiometer::readValueAvr(bool &changed){
	tempRead=0;
	for(int i=0; i<10; i++){
		tempRead+=analogRead(pin);
	}
	tempRead=tempRead/10;
	
	if(mapped)
	{
		tempRead=map(constrain(tempRead,inMin,inMax),inMin,inMax,0,127);
		}
	else
		tempRead=map(tempRead, 0, 1023, 0, 127);
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

void Potentiometer::changeSecondary( bool s){
	secondary=s;
}
