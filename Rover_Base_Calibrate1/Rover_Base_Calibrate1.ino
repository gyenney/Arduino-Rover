#include <Servo.h>
#include <Rover.h>

// This is a calibration program.  It moves the rover forward
// for 1 second, stops for 1 second, then moves backwards for 
// 1 second.  Tune the servo stop values (see the init function
// below) so the rover stops completely without any buzzing.  
// Use these stop values in other Rover programs.

Rover* rover;

void setup()
{
    Serial.begin(9600);
  
    rover = new Rover();
    rover->init(10,93,11,95);
    
    //  init parameters are: 
    //    Left Servo Pin = 10, 
    //    Left Servo Stop value = 90
    //    Right Servo Pin = 11
    //    Right Servo Stop value = 90
    //    
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
