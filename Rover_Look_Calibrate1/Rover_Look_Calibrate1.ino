#include <Servo.h>
#include <NewPing.h>
#include <LookRover.h>
#include <RangeRover.h>
#include <Rover.h>

//  This is a calibration program.  It causes the rover ping 
//  sensor to look forward, then right, then left repeatedly.
//  Use this program to tune the LOOK values so the sensor 
//  points in the correct directions.
//
//  NOTE:  1.  Be sure to have your battery pack turned on when
//             calibrating.  Otherwise you may get invalid results.
//        
//         2.  Be sure to set your servo stop values before 
//             calibrating these LOOK values.  Otherwise you 
//             may get invalid results.

// Tune these values to get the LOOK directions correct.
// You can also define new look directions by adding them here 
// and using your new values later in the program.
//
#define	  LOOK_RIGHT     36
#define	  LOOK_FORWARD   87
#define	  LOOK_LEFT      140

LookRover* rover;

void setup()
{
    Serial.begin(9600);
  
    rover = new LookRover();
    rover->init( 10, 90, 11, 90, 6, 5, 1000, 3);  
  
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

