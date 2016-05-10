/*
SMS_x_controller:

  Purpose:  A Signal ligh controller.  Detects a car about to run a red light and signals 
            to an oncoming smart-car to stop.
            
  Summary:
            If the East light-sensor turns off, there is an east-bound car.
            If the East light is red, and there is an east-bound car, the car is about to run a red light
            If North Light sensor turns off, there is a north-bound car.
            If there is a north-bound car and there is an east-bound car that is about to run the red-light, 
              the north-bound car needs to stop -- The signal light needs to send a STOP txt message.
              
  Next Steps:  
            Could use timers or more sensors to determine when the cars have passed through the intersection 
            and thus are out of danger.
            

MiddleSchoolOfEngineering
Author: Greg Yenney

*/

#include <SoftwareSerial.h>

const int myRx = 7;  // Shield: Rx=7, Tx=8
const int myTx = 8;  // Board:  Rx=4, Tx=2


const int myLightSensor = 0;
const int myNorthGreenLight = 10;
const int myNorthRedLight = 11;
const int myEastGreenLight = 12;
const int myEastRedLight = 13;

const int lightThreshold = 100;   // the light level that determines on and off.
int northlightLevel = 0;               // It's always good to initialize your variables.
int northlightIsOn = false;              // It's always good to initialize your variables.

int eastLightLevel = 0;               // It's always good to initialize your variables.
int eastLightIsOn = false;              // It's always good to initialize your variables.


char inputBuffer[256];

SoftwareSerial mySerial(myRx, myTx);

void setup()
{
  pinMode(myRx, INPUT_PULLUP);
  pinMode(myTx, OUTPUT);

  pinMode(myLightSensor, INPUT);
  
  pinMode(myNorthGreenLight, OUTPUT);  
  pinMode(myNorthRedLight, OUTPUT);
  pinMode(myEastGreenLight, OUTPUT);
  pinMode(myEastRedLight, OUTPUT);  

  mySerial.begin(19200);
  Serial.begin(19200);
 
  delay(100);
  mySerial.println("AT+IPR=19200");

  Serial.print("Test Signal Lights All On...");
  digitalWrite(myNorthGreenLight, HIGH);
  digitalWrite(myNorthRedLight, HIGH);
  digitalWrite(myEastGreenLight, HIGH);
  digitalWrite(myEastRedLight, HIGH);
  Serial.print("done.");
  Serial.println();
  
  delay(1000);

  digitalWrite(myNorthGreenLight, HIGH);
  digitalWrite(myNorthRedLight, LOW);
  digitalWrite(myEastGreenLight, LOW);
  digitalWrite(myEastRedLight, HIGH);

  Serial.println ("Press \'s <enter>\' to Send a message and press \'r <enter>\' to receive a message.");

  Serial.print("Waiting for LightIsOn...");
  while (lightLevel < lightThreshold)
  {
    lightLevel = analogRead(myLightSensor);
    lightIsOn = true;  
  }
  Serial.println("done.");

  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
}


void loop()
{

  //delay (100);
  lightLevel = analogRead(myLightSensor);

  Serial.print("Light level:  ");
  Serial.println(lightLevel);

  if (lightLevel < lightThreshold)
  {
    if (lightIsOn)
    {
      Serial.println("Light was turned off!");
      lightIsOn = false;  // Light is Off!
      SendMessage("EMERGENCY_STOP");

      digitalWrite(myNorthGreenLight, LOW);
      digitalWrite(myNorthRedLight, HIGH);
      digitalWrite(myEastGreenLight, LOW);
      digitalWrite(myEastRedLight, HIGH);
    }
  }
  else 
  {
    if (!lightIsOn)
    {
      Serial.println("Light was turned on!");
      lightIsOn = true;

      digitalWrite(myNorthGreenLight, HIGH);
      digitalWrite(myNorthRedLight, LOW);
      digitalWrite(myEastGreenLight, LOW);
      digitalWrite(myEastRedLight, HIGH);      
    }
  }


  if (Serial.available() > 0)
  {
     switch(Serial.read())
     {
        case 's':
          Serial.println("Send Message.");
          SendMessage("Hello from the Signal Light");
          break;
        default:
          break;
    }
  }


  for (int i = 0 ; i < 256 ; i++)
  {
      inputBuffer[i] = 0;
  }
      
  if (mySerial.available()>0)
  {
      mySerial.readBytes(inputBuffer, 255);
      Serial.write(inputBuffer);
  }   
}

void SendMessage(String message)
{
  Serial.println("SendMessage()");
  mySerial.println("AT+CMGS=\"phone_number_goes_here\"\r"); // Replace x with mobile number
  delay(100);
  mySerial.print("<Signal_Message=");// The SMS text you want to send
  delay(100);
  mySerial.print(message);
  delay(100);
  mySerial.println(">");
  mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(100);
}


