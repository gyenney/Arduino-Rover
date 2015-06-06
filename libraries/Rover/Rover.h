//
#ifndef Rover_h
#define Rover_h

#include <Arduino.h>
#include <Servo.h>

#define LEFT_TURN 	0
#define RIGHT_TURN 	1

class Rover
{
	private:
 
		int _servoLeftStop;
		int _servoRightStop;
		Servo _servoLeft;
		Servo _servoRight;
		int _debug;

 	public:
		Rover();

		void init ( int servoLeftPin,
			    int servoLeftStop,
			    int servoRightPin,
			    int servoRightStop );

		void go(int speed);

		void go(int speed,int time);

		void turn(int direction, int turnSpeed);

		void turn(int direction,int speed, int time);

		void Sweepturn(int direction, int speed);

		void stop();

		void stop(int time);

		void debugOn();

		void debugOff();

		void debugPrintln(char * str);

		void debugPrint(char * str);
};

#endif
