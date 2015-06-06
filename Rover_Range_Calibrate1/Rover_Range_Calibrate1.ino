#include <Servo.h>
#include <NewPing.h>
#include <RangeRover.h>
#include <RangeRover.h>
#include <Rover.h>

RangeRover* rover;
int dist_cm;

void setup()
{
    Serial.begin(9600);

    rover = new RangeRover();

    rover->init( 10, 91, 11, 89, 6, 5, 1000);

    // Left servo pin = 10
    // Left servo stop value
    // Right servo pin =11
    // Right servo stop value
    // Trigger Pin = 6
    // Echo Pin = 5
    // Max Distance
    //
    // Experiment to choose the best values
    // for stop for each servo.
    
    // use debugOn() to get debug messages in SerialMonitor
    rover->debugOff();
    rover->stop();  // begin with the rover stopped.

}


void loop()
{
    dist_cm = rover->range();  // get the range in cm.
    Serial.print("Range is: ");
    Serial.println(dist_cm);
    
    rover->stop(1000);   // Wait 1 second before next range reading.
    
}
