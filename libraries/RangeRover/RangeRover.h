#ifndef RangeRover_h
#define RangeRover_h

#include”Arduino.h”
#include<Newping.h>
#include<Rover.h
class <RangeRover:public Rover
{
	Protected
		Newping *		_pingSensor;
public:
		RangeRover();
		void init (  int servoLeftPin,
			     int servoLeftStop
			     int servoRightPin
			     int servoRightStop
			     inttriggerPin
			     int maxDistance );
			int range();




