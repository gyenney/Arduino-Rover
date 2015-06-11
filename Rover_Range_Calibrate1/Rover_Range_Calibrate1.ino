#include <Servo.h>
#include <NewPing.h>
#include <RangeRover.h>
#include <RangeRover.h>
#include <Rover.h>


//  This is a calibration program.  It takes distance readings 
//  using the ping sensor and writes the measurements on the 
//  Serial Monitor.  Run this program and use the Serial Monitor 
//  (Tools --> Serial Monitor), to validate that the results 
//  displayed match what you expect.  These sensors  do provide 
//  odd and incorrect results from time to time.  It is 
//  important to know that and to what sorts of results the 
//  sensor returns.
//
//  NOTE:  1.  Be sure to have your battery pack turned on when
//             calibrating.  Otherwise you may get invalid results.
//        
//         2.  Be sure to set your servo stop values before 
//             calibrating these LOOK values.  Otherwise you 
//             may get invalid results.



RangeRover* rover;
int dist_cm;

void setup()
{
    Serial.begin(9600);

    rover = new RangeRover();

    rover->init( 10, 9, 11, 95, 6, 5, 1000);

    //  init parameters: 
    //    Left Servo Pin = 10, 
    //    Left Servo Stop value = 90
    //    Right Servo Pin = 11
    //    Right Server Stop value = 90 
    //    Trigger Pin = 6
    //    Echo Pin = 5
    //    Max Distance = 1000  (adjust if desired)
    //
    // Tune the stop values, so the servos fully stop. 
    
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
