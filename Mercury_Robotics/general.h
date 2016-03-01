/*
	move generalize functions here
	place them under namespace
*/

#ifndef GENERAL_H
#define GENERAL_H

#include <Wire.h>
#include <motor.h>
#include <sensor.h>
#include <usb_communication.h>

namespace general {
	// move normalize() here!!!  one day
} // namespace general

namespace servo {
void setup() {
	claw.begin();
	claw.set_freq();
	elbow.begin();
	elbow.set_freq();
	theta.begin();
	theta.set_freq();
	wrist.begin();
	wrist.set_freq();
}

void tall() {
	theta.set_position(480);
	elbow.set_position(340);
	wrist.set_position(420);
}
	
void pickup() {
	theta.set_position(480);
	elbow.set_position(160);
	wrist.set_position(225);		
}
	
void look() {
	
}
	
void load() {
	
}
} // namespace servo

#endif