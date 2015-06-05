#ifndef LookRover_h
#define LookRover_h


#include "Arduino.h"
#include <Servo.h>
#include <NewPing.h>
#include <RangeRover.h>

class LookRover:public RangerRover
{
 protected:
           Servo	_faceServo;
public:
	LookRover();
	void init(	int servoLeftPin,
			int servoLeftStop,
			int servoRightPin,
			int servoRightStop,
			int triggerPin,
			int echoPin,
			int maxDistance,
'			int faceServoPin,
			);
			
			void look(int direction);
};

#endif