/*
STEM Center USA, Inc.
Pi-Bot: Motor Test Program using Function Calls
*/

#include <SoftwareSerial.h>

const int myRx = 6;  // Shield: Rx=7, Tx=8
const int myTx = 5;  // Board:  Rx=2, Tx=4

char inputBuffer[256];

SoftwareSerial mySerial(myRx, myTx);

const int In1 = 3;      
const int In2 = 5;      
const int In3 = 6;      
const int In4 = 11;  

int sensorPin = 9;
int highPin = 10;
int lowPin = 11;
int val;

void setup()
{
  pinMode(sensorPin, INPUT_PULLUP);
  pinMode(highPin, OUTPUT);
  pinMode(lowPin, OUTPUT);
  
  // initialize the pins an output:
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
  
  pinMode(myRx, INPUT_PULLUP);
  pinMode(myTx, OUTPUT);

  mySerial.begin(19200);
  Serial.begin(19200);
  delay(100);

  Serial.println ("about to set modem baudrate.");
  mySerial.println((char)26);
  mySerial.println((char)26);
  mySerial.println("AT+IPR=19200");

  Serial.println("Done.");

  Serial.println ("Press \'s <enter>\' to Send a message and press \'r <enter>\' to receive a message.");
  digitalWrite(highPin, HIGH);
  digitalWrite(lowPin, LOW);
}
void loop()
{
  delay(5000);
  val = digitalRead(sensorPin);
  
  
  int speed1, speed2;
  int delayTime;
  speed1 = 150;
  speed2 = 150;



  
  if (val == HIGH)
  {
    Serial.println('t');
    //Stop();
  }
  else
  {
   Serial.println('g');
   //Go();
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

        case 't':
          Stop();
          break;
          
        case 'g':
          Go();
          break;
    }
    
  }
  

  if (mySerial.available())
  {
    Serial.write(mySerial.read());
  }

     /*
  if (mySerial.available()>0)
  {
      mySerial.readBytes(inputBuffer, 255);
      Serial.println("DUMP DATA");
      Serial.println(inputBuffer);
      Serial.println("END DUMP DATA");
  }
       */ 
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
  mySerial.println("AT+CMGS=\"8057270090\"\r"); // Replace x with mobile number
  delay(500);
  mySerial.println("Hi dylan.");// The SMS text you want to send
  delay(500);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(100);
}

void Stop()
{
  Serial.println("Stop()");
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"8057270090\"\r"); // Replace x with mobile number
  delay(500);
  mySerial.println("Stop");// The SMS text you want to send
  delay(500);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(100);
 
  
}
void Go()
{
  Serial.println("Go()");
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"8057270090\"\r"); // Replace x with mobile number
  delay(500);
  mySerial.println("Go");// The SMS text you want to send
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
 
 
