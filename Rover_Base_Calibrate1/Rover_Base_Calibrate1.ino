#include <Servo.h>
#include <Rover.h>

Rover* rover;

void setup()
{
    Serial.begin(9600);
  
    rover = new Rover();
    rover->init(10,88,11,89);
    //  init parameters: 
    //    Left Servo Pin = 10, 
    //    Left Servo Stop value = 90
    //    Right Servo Pin = 11
    //    Right Server Stop value = 90
    // Tune the stop values, so the servos fully stop.  

 
  
    // debugOn() and debugOff() turn debugging messages on/off in the SerialMonitor
    rover->debugOff();
    rover->stop();  
  
    Serial.println ("Adjust the Servo Left Stop and Servo Right Stop values until the servos completely stop when stop command is given.");
    Serial.println ("Use the stop values found, in future programs on this rover.");
}

void loop()
{

    Serial.println("Go forward for 1 second.");
    rover->go(20,1000);
 
    Serial.println("Stop for 1 second.");
    rover->stop(1000);
  
    Serial.println("Go backward for 1 second.");
    rover->go(-20,1000);

    Serial.println("Stop for 1 second.");
    rover->stop(1000);
  
}
