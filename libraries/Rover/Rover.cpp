/*
    Rover.cpp - Library for driving a rover around.
    Created by: Greg Yenney
*/

#include"Arduino.h"
#include <Servo.h>
#include <Rover.h>


Rover::Rover()
{
	 //debugPrintln("");
}

void Rover::init(	int servoLeftPin,
                 	int servoLeftStop,
                 	int servoRightPin,
   	  	        int servoRightStop)

{
    
    _servoLeftStop      =servoLeftStop;
    

    _servoRightStop    	=servoRightStop;


    _servoLeft.attach(servoLeftPin);
    _servoRight.attach(servoRightPin);

}

void Rover::stop()
{
    _servoLeft.write(_servoLeftStop);
    _servoRight.write(_servoRightStop);
}

void Rover::stop(int time)
{
	stop();
	delay(time);
}

void Rover::go(int speed)
{
    _servoLeft.write(_servoLeftStop - speed);
    _servoRight.write(_servoRightStop + speed);
}



void Rover::go(int speed,int time)
{
	go(speed);
	delay(time);
}

void Rover::turn(int direction, int turnSpeed)
{
    if(RIGHT_TURN == direction)
    {
   	 _servoLeft.write(_servoLeftStop + turnSpeed);
   	 _servoRight.write(_servoRightStop + turnSpeed);
    }
    else
    {
   	 _servoLeft.write(_servoLeftStop - turnSpeed);
   	 _servoRight.write(_servoRightStop - turnSpeed);
    }
}

void Rover::Sweepturn(int direction, int turnSpeed)
{
    if(RIGHT_TURN == direction)
    {
   	 _servoLeft.write(_servoLeftStop - turnSpeed/2);
   	 _servoRight.write(_servoRightStop + turnSpeed);
    }
    else
    {
   	 _servoLeft.write(_servoLeftStop - turnSpeed);
   	 _servoRight.write(_servoRightStop - turnSpeed);
    }
}



void Rover::turn(int direction, int speed, int time)
{
	turn(direction,speed);
	delay(time);
	stop();
}


void Rover::debugOn()
{
	_debug = 1;
}

void Rover::debugOff()
{
	_debug = 0;
}

void Rover::debugPrintln(char * str)
{
	if(_debug)
	{
		Serial.println(str);
	}
}

void Rover::debugPrint(char * str)
{
	if(_debug)
	{	
		Serial.print(str);
	}
}    
