/*
MiddleSchoolOfEngineering

SMS_Txt -- SMS test program.

Greg Yenney
*/

#include <SoftwareSerial.h>

const int myRx = 7;  // Shield: Rx=7, Tx=8
const int myTx = 8;  // Board:  Rx=4, Tx=2

const String phone_number = "xxxxxxxxxx";

char inputBuffer[256];

SoftwareSerial mySerial(myRx, myTx);

void setup()
{
  pinMode(myRx, INPUT_PULLUP);
  pinMode(myTx, OUTPUT);

  mySerial.begin(19200);
  Serial.begin(19200);

  delay(100);
  mySerial.println("AT+IPR=19200");

  Serial.println ("Press \'s <enter>\' to Send a message and press \'r <enter>\' to receive a message.");

}
void loop()
{

  if (Serial.available() > 0)
  {
     switch(Serial.read())
     {
        case 's':
          Serial.println("Send Message.");
          SendMessage();
          break;

        case 'n':
          Serial.println("Get IMEI number.");
          doATCmd("AT+CGSN");
          break;
          
        case 'p':        
          Serial.println("Get phone number.");
          doATCmd("AT+CNUM");
          break;

        case 'i':
          Serial.println("Get CIMI");
          doATCmd("AT+CIMI");
          break;

        case 'k':
          Serial.println("Get Clock.");
          doATCmd("AT+CCLK?");
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



void SendMessage()
{
  Serial.println("SendMessage()");
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.print("AT+CMGS=\"");
  mySerial.print(phone_number);
  mySerial.println("\"\r");
  delay(500);
  mySerial.println("Hello, from device.");// The SMS text you want to send
  delay(500);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(100);
}




String doATCmd(String atCmd)
{
  Serial.println("Doing AT Command:  atCmd");
  mySerial.println(atCmd);  
}

