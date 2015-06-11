#include <Servo.h>
#include <NewPing.h>
#include <LookRover.h>
#include <RangeRover.h>
#include <Rover.h>

//  This program drives a rover around.  
//  The intended algorithm is go until it comes within 20cm 
//  of an obstacle, then looks right, forward, and 
//  left to determine the most open path.  Then turn that 
//  direction and continue on.  If it has no room, it will first 
//  back up then turn right and move on.
//  Refine and this code to handle more situations.  
//  Add routines directly into the base libraries to make them 
//  available and easy to use for all rover developers.
//
//  NOTE:  1.  Be sure to have your battery pack turned on when
//             calibrating.  Otherwise you may get invalid results.
//        
//         2.  Be sure to set your servo stop values before 
//             calibrating these LOOK values.  Otherwise you 
//             may get invalid results.




//  Tune these LOOK values to get the Sensor to look 
//  in the directions indicated correctly.
//
#define	  LOOK_RIGHT     36 
#define	  LOOK_FORWARD   87
#define	  LOOK_LEFT      140

LookRover* rover;

int dist_forward;
int dist_right;
int dist_left;

int most_open_path = 0;
int turn_direction = NULL_TURN;

void setup()
{
    Serial.begin(9600);
  
    rover = new LookRover();
    rover->init( 10, 93, 11, 95, 6, 5, 1000, 3);  
  
    //  init parameters are: 
    //    Left Servo Pin = 10, 
    //    Left Servo Stop value = 90
    //    Right Servo Pin = 11
    //    Right Servo Stop value = 90
    //    Trigger Pin = 6
    //    Echo Pin = 5
    //    Max Distance (in cm)
    //    Face Servo Pin = 3
    //    
    // Tune the stop values, so the servos fully stop.  

    // Use debugOn() to get debug messages in SerialMonitor
    rover->debugOff();   
    rover->stop();
    rover->look(LOOK_FORWARD);
}



void loop()
{
  
    // This section causes the rover to look around and 
    // measure the distances, right, forward and left.
    
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


    //  This section finds the most open direction 
    //  then sets "most_open_path" to that value.
    
    most_open_path = 0;
    if (dist_left > most_open_path)
    {
         most_open_path = dist_left;
         turn_direction = LEFT_TURN;
    }
    if (dist_forward > most_open_path)
    {
         most_open_path = dist_forward;
         turn_direction = NULL_TURN;
    }
    if (dist_right > most_open_path)
    {
         most_open_path = dist_right;
         turn_direction = RIGHT_TURN;
    }
    
    
    //  This section tells the rover what to do based 
    //  on the most_open_direction that was found.
    
    if (LEFT_TURN == turn_direction)
    {
          Serial.println("Turning left.");
          rover->turn(LEFT_TURN, 10, 1000);
        
    } else if (RIGHT_TURN == turn_direction)
    {
          Serial.println("Turning right.");
          rover->turn(RIGHT_TURN, 10, 1000);

    } else if (NULL_TURN == turn_direction)
    {
          Serial.println("Go backwards then turn right.");
          rover->go(-10, 1000);
          rover->turn(RIGHT_TURN, 10, 1000);
    }

    //  Now that the rover has handled the obstacle 
    //  (with the above code), tell the rover to go 
    //  forward until it detects a new obstacle.  
    //  It will then stop and return to the beginning of 
    //  this loop function where it will start by looking 
    //  around and then doing above obstacle avoidance actions.
    
    while (rover->range() > 20)
    {
          Serial.println("Go at speed 20 until range is less than 20.");
          rover->go(20);
    }
    rover->stop();
}

