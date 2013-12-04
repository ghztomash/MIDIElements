// MIDI Elements RGLed class
// Library to simplifly handling of compontents for MIDI controllers
// Created by Tomash Ghz
// www.tomashg.com
// ghz.tomash@gmail.com

#include "RGLed.h"

//-----------------------------------------------------------------------------------
// constructor
RGLed::RGLed(byte pa, byte pb){
	RGLed(pa,pb,0,0,false);
}

RGLed::RGLed(byte pa, byte pb, byte c, byte n){
	RGLed(pa,pb,c,n,false);
}

RGLed::RGLed(byte pa, byte pb, byte c, byte n, bool a){
	pinA=pa;
	pinB=pb;
	channel=c;
	number=n;
	pwm=a;
	state=0;
	
	pinMode(pinA,OUTPUT);
	pinMode(pinB,OUTPUT);
}

// destructor
RGLed::~RGLed(){
}

void RGLed::setOn(byte c, byte n, byte v){
	if((channel==c)&&(number==n)){
		if(v==0) {// velocity 0 turn RGLed off
			analogWrite(pinA,0);
			analogWrite(pinB,0);
		}else // turn RGLed on
		{
			if(pwm){ // analog write
				analogWrite(pinA,map(v,0,127,0,255));
				}
			else{
					switch(v%3){
						case 0: analogWrite(pinA,64);
									analogWrite(pinB,0);
									break;
						case 1: analogWrite(pinB,64);
									analogWrite(pinA,0);
									break;
						case 2: analogWrite(pinA,64);
									analogWrite(pinB,64);
									break;
						}
				}
			state=v;
		}
		
	}
}

void RGLed::setOff(byte c, byte n, byte v){
	if((channel==c)&&(number==n)){ // note off, turn RGLed off
			analogWrite(pinA,0);
			analogWrite(pinB,0);
			state=0;
	}
}

void RGLed::setOnSilent(byte c, byte n, byte v){
	if((channel==c)&&(number==n)){
		if(v==0){ // velocity 0 turn RGLed off
			state=0;
			}
		else // turn RGLed on
		{
			state=v;
		}
		
	}
}

void RGLed::setOffSilent(byte c, byte n, byte v){
	if((channel==c)&&(number==n)){ // note off, turn RGLed off
			state=0;
	}
}

void RGLed::set(byte s){
	state=s;
}

void RGLed::set(){
	if(state!=0){
		switch(state%3){
			case 0: analogWrite(pinA,64);
						analogWrite(pinB,0);
						break;
			case 1: analogWrite(pinB,64);
						analogWrite(pinA,0);
						break;
			case 2: analogWrite(pinA,64);
						analogWrite(pinB,64);
						break;
			}
		}
	else{
		analogWrite(pinA,0);
		analogWrite(pinB,0);
		}
}