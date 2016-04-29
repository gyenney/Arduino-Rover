/*
 * Greg Yenney
 * 
 * SMS_Light_Sensor
 *    Checks the ambient light level and sends txt message when light comes on or goes off.
 */

#include <SoftwareSerial.h>




const int myRx = 7;  // Shield: Rx=7, Tx=8
const int myTx = 8;  // Board:  Rx=4, Tx=2
const int myLightSensor = 0;
int light_level;
int light_on;

char inputBuffer[256];

SoftwareSerial mySerial(myRx, myTx);






void setup()
{
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

}

void SendMessage()
{
  Serial.println("SendMessage()");
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"8057270090\"\r"); // Replace x with mobile number
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
  
