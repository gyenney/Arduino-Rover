/*
STEM Center USA, Inc.
Pi-Bot: Motor Test Program using Function Calls
*/

#include <SoftwareSerial.h>

const int myRx = 7;  // Shield: Rx=7, Tx=8
const int myTx = 8;  // Board:  Rx=4, Tx=2
const int myLightSensor = 0;
int light_level;
int light_on;

char inputBuffer[256];

SoftwareSerial mySerial(myRx, myTx);

const int In1 = 3;      
const int In2 = 5;      
const int In3 = 6;      
const int In4 = 11;  


void setup()
{
  // initialize the pins an output:
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
  
  pinMode(myRx, INPUT_PULLUP);
  pinMode(myTx, OUTPUT);
  pinMode(myLightSensor, INPUT);

  mySerial.begin(19200);
  Serial.begin(19200);
  delay(100);
  
  mySerial.println("AT+IPR=19200");

  Serial.println ("Press \'s <enter>\' to Send a message and press \'r <enter>\' to receive a message.");

}
void loop()
{

  delay (1000);
  light_level = analogRead(myLightSensor);
  
  Serial.print("Light Level:  ");
  Serial.print(light_level);
  Serial.println();
 

  if (light_level > 100)
  {
      if (light_on == 0)
      {
          light_on = 1;
          Serial.println("Light was turned on!");
          SendOnMessage();
      }
  }
  else
  {
      if (light_on == 1)
      {
          light_on = 0;
          Serial.println("Light was turned off!");
          SendOffMessage();
      }
  }

  
  int speed1, speed2;
  int delayTime;
  speed1 = 150;
  speed2 = 150;

  if (Serial.available() > 0)
  {
     switch(Serial.read())
     {
        case 's':
          Serial.println("Send Message.");
          SendMessage();
          break;
        case 'r':
          Serial.println("Receive Message.");
          ReceiveMessage();
          break;
    }
  }
  
     
  if (mySerial.available()>0)
  {
      mySerial.readBytes(inputBuffer, 255);
      Serial.write(inputBuffer);
  }
        
  /*
        forward(speed1, speed2);
        delay(2000);
        stopNow();
        delay(1000);
        reverse(speed1, speed2);
        delay(1000);
        stopNow();
        delay(1000);
        */
  
}


void forward(int speed1, int speed2)
{
analogWrite(In4, 0);
analogWrite(In3, speed1);
analogWrite(In2, 0);
analogWrite(In1, speed2);
}
void reverse (int speed1, int speed2)
{
analogWrite(In4, speed1);
analogWrite(In3, 0);
analogWrite(In2, speed2);
analogWrite(In1, 0);
return;
}
void stopNow()
{
analogWrite(In4, 0);
analogWrite(In3, 0);
analogWrite(In2, 0);
analogWrite(In1, 0);
return;
}

void SendMessage()
{
  Serial.println("SendMessage()");
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"your_phone_number\"\r"); // Replace x with mobile number
  delay(500);
  mySerial.println("Hello, from Rover2.");// The SMS text you want to send
  delay(500);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(100);
}


void SendOnMessage()
{
  Serial.println("SendMessage()");
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"8057270090\"\r"); // Replace x with mobile number
  delay(500);
  mySerial.println("Light was turned on!");// The SMS text you want to send
  delay(500);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(100);
}


void SendOffMessage()
{
  Serial.println("SendMessage()");
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"8057270090\"\r"); // Replace x with mobile number
  delay(500);
  mySerial.println("Light was turned off!");// The SMS text you want to send
  delay(500);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(100);
}


void ReceiveMessage()
{
  Serial.println("ReceiveMessage()");
  mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
  delay(1000);
 }
 
 
 

void GetTime()
{
   mySerial.println("AT+CLTS=");
   delay(1000);
}
 
 
