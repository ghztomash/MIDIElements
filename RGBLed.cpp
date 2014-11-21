// MIDI Elements RGBLed class
// Library to simplify handling of components for MIDI controllers
// Created by Tomash Ghz
// www.tomashg.com
// ghz.tomash@gmail.com

#include "RGBLed.h"

//-----------------------------------------------------------------------------------
// constructor
RGBLed::RGBLed(byte pa, byte pb, byte pc){
	RGBLed(pa,pb,0,0,false);
}

RGBLed::RGBLed(byte pa, byte pb, byte pc, byte c, byte n){
	RGBLed(pa,pb,c,n,false);
}

RGBLed::RGBLed(byte pa, byte pb, byte pc, byte c, byte n, bool a){
	pinA=pa;
	pinB=pb;
	pinC=pc;
	channel=c;
	number=n;
	pwm=a;
	state=0;
	red=0;
	green=128;
	blue=0;
	intensity=128;
	pinMode(pinA,OUTPUT);
	pinMode(pinB,OUTPUT);
	pinMode(pinC,OUTPUT);
}

// destructor
RGBLed::~RGBLed(){
}

void RGBLed::setOn(byte c, byte n, byte v){
	if((channel==c)&&(number==n)){
		if(v==0) {// velocity 0 turn RGBLed off
			analogWrite(pinA,0);
			analogWrite(pinB,0);
			analogWrite(pinC,0);
		}else if(v==127){ // turn on selected color
			analogWrite(pinA,red);
			analogWrite(pinB,green);
			analogWrite(pinC,blue);
		}else // turn RGBLed on
		{
			if(pwm){ // analog write
				analogWrite(pinA,map(v,0,127,0,255));
				analogWrite(pinB,map(v,0,127,0,255));
				analogWrite(pinC,map(v,0,127,0,255));
				}
			else{
					switch(v%7){
						case 0:
							analogWrite(pinA,intensity);
							analogWrite(pinB,0);
							analogWrite(pinC,0);
							break;
						case 1:
							analogWrite(pinA,0);
							analogWrite(pinB,intensity);
							analogWrite(pinC,0);
							break;
						case 2:
							analogWrite(pinA,0);
							analogWrite(pinB,0);
							analogWrite(pinC,intensity);
							break;
						case 3:
							analogWrite(pinA,intensity);
							analogWrite(pinB,intensity);
							analogWrite(pinC,0);
							break;
						case 4:
							analogWrite(pinA,intensity);
							analogWrite(pinB,0);
							analogWrite(pinC,intensity);
							break;
						case 5:
							analogWrite(pinA,0);
							analogWrite(pinB,intensity);
							analogWrite(pinC,intensity);
							break;
						case 6:
							analogWrite(pinA,intensity);
							analogWrite(pinB,intensity);
							analogWrite(pinC,intensity);
							break;
						}
				}
			state=v;
		}
	}
}

void RGBLed::setOff(byte c, byte n, byte v){
	if((channel==c)&&(number==n)){ // note off, turn RGBLed off
			analogWrite(pinA,0);
			analogWrite(pinB,0);
			analogWrite(pinC,0);
			state=0;
	}
}

void RGBLed::setOnSilent(byte c, byte n, byte v){
	if((channel==c)&&(number==n)){
		if(v==0){ // velocity 0 turn RGBLed off
			state=0;
			}
		else // turn RGBLed on
		{
			state=v;
		}
	}
}

void RGBLed::setOffSilent(byte c, byte n, byte v){
	if((channel==c)&&(number==n)){ // note off, turn RGBLed off
			state=0;
	}
}

void RGBLed::set(byte s){
	state=s;
}

void RGBLed::set(){
	if(state==0){
		analogWrite(pinA,0);
		analogWrite(pinB,0);
		analogWrite(pinC,0);
	}
	else if(state==127){ // turn on selected color
		analogWrite(pinA,red);
		analogWrite(pinB,green);
		analogWrite(pinC,blue);
	}
	else{
		switch(state%3){
			case 0:
				analogWrite(pinA,intensity);
				analogWrite(pinB,0);
				analogWrite(pinC,0);
				break;
			case 1:
				analogWrite(pinA,0);
				analogWrite(pinB,intensity);
				analogWrite(pinC,0);
				break;
			case 2:
				analogWrite(pinA,0);
				analogWrite(pinB,0);
				analogWrite(pinC,intensity);
				break;
			case 3:
				analogWrite(pinA,intensity);
				analogWrite(pinB,intensity);
				analogWrite(pinC,0);
				break;
			case 4:
				analogWrite(pinA,intensity);
				analogWrite(pinB,0);
				analogWrite(pinC,intensity);
				break;
			case 5:
				analogWrite(pinA,0);
				analogWrite(pinB,intensity);
				analogWrite(pinC,intensity);
				break;
			case 6:
				analogWrite(pinA,intensity);
				analogWrite(pinB,intensity);
				analogWrite(pinC,intensity);
				break;
			}
		}
}

// set the on colors manually. on color is enabled if velocity 127 is recieved.
void RGBLed::setColor(byte r, byte g, byte b, byte i){
	red=r;
	green=g;
	blue=b;
	intensity=i;
}