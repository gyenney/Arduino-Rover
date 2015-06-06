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

int dist_forward;
int dist_right;
int dist_left;

void setup()
{
    Serial.begin(9600);
  
    rover = new LookRover();
    rover->init( 10, 90, 11, 89, 6, 5, 1000, 3);  
  
    //  init parameters: 
    //    Left Servo Pin = 10, 
    //    Right Servo Pin = 11
    //    Trigger Pin = 6
    //    Echo Pin = 5
    //    Max Distance
    //    Face Servo Pin = 3                  
    // Tune the stop values, so the servos fully stop.  

    // do debugOn() to get debug messages in SerialMonitor
    rover->debugOff();   
    rover->stop();
    rover->look(LOOK_FORWARD);
}



void loop()
{
    rover->look(LOOK_RIGHT);
    rover->stop(1000); 
    dist_right = rover->range();
  
    rover->look(LOOK_FORWARD);
    rover->stop(1000); 
    dist_forward = rover->range();

    rover->look(LOOK_LEFT);
    rover->stop(1000); 
    dist_left = rover->range();
    
    rover->look(LOOK_FORWARD);

    Serial.print("left distance   : ");
    Serial.println(dist_left);
    Serial.print("forward distance   : ");
    Serial.println(dist_forward);
    Serial.print("right distance   : ");
    Serial.println(dist_right);  
}

