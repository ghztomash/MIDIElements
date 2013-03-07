// MIDI Elements LED class
// Library to simplifly handling of compontents for MIDI controllers
// Created by Tomash Ghz
// www.tomashg.com
// ghz.tomash@gmail.com

#include "Led.h"

//-----------------------------------------------------------------------------------
// constructor
Led::Led(byte p){
	Led(p,0,0,false);
}

Led::Led(byte p, byte c, byte n){
	Led(p,c,n,false);
}

Led::Led(byte p, byte c, byte n, bool a){
	pin=p;
	channel=c;
	number=n;
	pwm=a;
	
	pinMode(pin,OUTPUT);
}

// destructor
Led::~Led(){
}

void Led::setOn(byte c, byte n, byte v){
	if((channel==c)&&(number==n)){
		if(v==0) // velocity 0 turn led off
			digitalWrite(pin,LOW);
		else // turn led on
		{
			if(pwm) // analog write
				analogWrite(pin,map(v,0,127,0,255));
			else
				digitalWrite(pin,HIGH);
		}
	}
}

void Led::setOff(byte c, byte n, byte v){
	if((channel==c)&&(number==n)){ // note off, turn led off
			digitalWrite(pin,LOW);
	}
}
