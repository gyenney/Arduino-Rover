/*
  RangeRover.cpp - Library for checking range on a rover.
  Created by: Greg Yenney
*/

#include <Arduino.h>
#include <RangeRover.h>

RangeRover::RangeRover()
{
	debugPrintln("In Constructor RangeRover::RangeRover");
}

void RangeRover::init ( int servoLeftPin,
		  	int servoLeftStop,
		   	int servoRightPin,
			int servoRightStop,
			int triggerPin,
			int echoPin,
			int maxDistance  )
{
	debugPrintln("In method RangeRover::init()");

	_pingSensor = new NewPing( triggerPin, echoPin, maxDistance);

	Rover::init( 	servoLeftPin, 
			servoLeftStop, 
			servoRightPin, 
			servoRightStop  );
}


int RangeRover::range()
{
		debugPrintln("In method RangeRover::range()");

		int dist_cm = _pingSensor->ping_cm();

		return (dist_cm);
}
