// MIDI Elements empty template
// by Tomash Ghz
// www.tomashg.com
// ghz.tomash@gmail.com

#include <MIDIElements.h>

boolean debug = false; // print to serial instead of midi
boolean secondary = true; // enable secondary midi messages
int midiChannel = 1; // midi channel number

// pins used in this exapmle are ones in corner of board, so:
// 11 & 12 for Teensy 3.x
// 16 & 17 for Teensy 2.0++
int butPin1 = 11; // digital pin for reading first button
int butPin2 = 12; // digital pin for reading second button

int potPin = 21; // analog pin A7 for Teensy 3.x, for Teensy 2.0++ change this to 45
int ledPin = 3; // PWM pin 3 for Teensy 3.x, for Teensy 2.0++ change this to 15



// declare all your components here
Button but(butPin1, midiChannel, 1, secondary, debug); // button 1 on pin 17
Button but2(butPin2, midiChannel, 2, secondary, debug); // button 2 on pin 16
Potentiometer pot(potPin, midiChannel, 3, secondary, debug); // knob on pin 45 (A7)
Led led(ledPin, midiChannel, 3, true); // led on pin 15 with PWM enabled, triggered on the same CC number as pot

void setup()
{
  usbMIDI.setHandleNoteOff(OnNoteOff); //set event handler for note off
  usbMIDI.setHandleNoteOn(OnNoteOn); //set event handler for note on
  usbMIDI.setHandleControlChange(OnControlChange); // set event handler for CC
}

void loop()
{

  // add here all the input component reads
  pot.read(); // read knob and send midi messages
  but.read(); // read buttons and send midi messages
  but2.read();

  usbMIDI.read(); // read all the incoming midi messages
}

//====================================================================
// event handlers
void OnNoteOn(byte channel, byte note, byte velocity)
{
  // add all your output component sets that will trigger with note ons
  led.setOn(channel, note, velocity);
}

void OnNoteOff(byte channel, byte note, byte velocity)
{
  // add all your output component sets that will trigger with note ons
  led.setOff(channel, note, velocity);
}

void OnControlChange(byte channel, byte control, byte value)
{
  // add all your output component sets that will trigger with cc
  led.setOn(channel, control, value);
}