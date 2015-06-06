#ifndef RangeRover_h
#define RangeRover_h

#include <Arduino.h>
#include <NewPing.h>
#include <Rover.h>

class RangeRover : public Rover
{
	protected:

		NewPing * _pingSensor;

	public:

		RangeRover();
		void init (  int servoLeftPin,
			     int servoLeftStop,
			     int servoRightPin,
			     int servoRightStop,
			     int triggerPin,
			     int echoPin,
			     int maxDistance );

		int range();

};

#endif
