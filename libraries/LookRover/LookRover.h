#ifndef LookRover_h
#define LookRover_h

#include "Arduino.h"
#includ <Servo.h>
#include <NewPing.h>
#include <RangeRover.h>

class LookRover : public RangeRover
{
 protected:
	   Servo	_faceServo;

 public:
		LookRover();
		void init(	int servoLeftPin,
				int servoLeftStop,
				int servo
