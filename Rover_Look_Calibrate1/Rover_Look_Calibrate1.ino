#include <Servo.h>
#include <NewPing.h>
#include <LookRover.h>
#include <RangeRover.h>
#include <Rover.h>

// Tune these values to get the look directions correct.
#define	  LOOK_RIGHT     42
#define	  LOOK_FORWARD   87
#define	  LOOK_LEFT      138

LookRover* rover;

void setup()
{
    Serial.begin(9600);
  
    rover = new LookRover();
    rover->init( 10, 90, 11, 89, 6, 5, 1000, 3);  
  
    //  init parameters: 
    //    Left Servo Pin = 10, 
    //    Left Servo Stop value = 90 (adjust appropriately)
    //    Right Servo Pin = 11
    //    Right Server Stop value = 90 (adjust appropriately)
    //    Trigger Pin = 6
    //    Echo Pin = 5
    //    Max Distance = 1000  (adjust if desired)
    //    Face Servo Pin = 3                  
    // Tune the stop values, so the servos fully stop.  

    // do debugOn() to get debug messages in SerialMonitor
    rover->debugOff();    
    rover->stop();   // make sure rover is stopped to begin
    
    Serial.println ("Adjust the LOOK_RIGHT, LOOK_FORWARD, LOOK_LEFT values until the face servo looks in the proper directions.");
    Serial.println ("Use the values found, in future programs for this rover.");
}



void loop()
{
    Serial.println ("Look forward.");
    rover->look(LOOK_FORWARD);
    rover->stop(1000);   // stop and wait for 1 second.
 
    Serial.println ("Look right.");
    rover->look(LOOK_RIGHT);
    rover->stop(1000); 
  
    Serial.println ("Look forward.");
    rover->look(LOOK_FORWARD);
    rover->stop(1000); 

    Serial.println ("Look left.");
    rover->look(LOOK_LEFT);
    rover->stop(1000);   
}

