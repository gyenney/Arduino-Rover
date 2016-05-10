#include <Servo.h>
#include <Rover.h>

Rover* rover;

const int goPin = 13;
int goPinState = LOW;


void setup()
{
    Serial.begin(9600);
  
    pinMode(goPin, INPUT);
  
    rover = new Rover();
    rover->init(10,93,11,94);
    
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

}

void loop()
{
    goPinState = digitalRead(goPin);

    if (goPinState == HIGH)
    {
       Serial.println ("State is Go.");
       rover->go(20);
    } else
    {
       Serial.println ("State is Stop.");
       rover->stop();
    }
    

}
