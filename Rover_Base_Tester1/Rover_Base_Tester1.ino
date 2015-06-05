#include <Servo.h>
#include <Rover.h>

Rover* rover;

void setup()
{
  Serial.begin(9600);
  
  rover = new Rover();
  rover->init(10,91,11,89);
  rover->debugOff();
  
}

void loop()
{
  
  rover->Sweepturn(RIGHT_TURN, 15);
  /*rover->stop(1000);
  
  Serial.println("forward");
  rover->go(20,1000);
  rover->stop(1000);
  
  Serial.println("Backward");
  rover->go(-20,1000);
  rover->stop(1000);
  
  Serial.println("Turn left");
  rover->turn(LEFT_TURN,10,1000);
  rover->stop(1000);
  
  Serial.println("Turn right");
  rover->turn(RIGHT_TURN,10,1000);
  rover->stop(1000);
*/

}
