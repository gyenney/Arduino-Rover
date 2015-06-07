#include <Servo.h>
#include <NewPing.h>
#include <LookRover.h>
#include <RangeRover.h>
#include <Rover.h>

// Tune these values to get the look directions correct.
#define	  LOOK_RIGHT     42
#define	  LOOK_FORWARD   95
#define	  LOOK_LEFT      150

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
    rover->init( 10, 88, 11, 89, 6, 5, 1000, 3);  
  
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
    
    while (rover->range() > 20)
    {
          Serial.println("Go at speed 20 until range is less than 20.");
          rover->go(20);
    }
    rover->stop();
}

