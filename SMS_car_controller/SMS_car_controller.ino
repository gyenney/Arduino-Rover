/*
SMS_car_controller:

  Purpose:  A Signal ligh controller.  Detects a car about to run a red light and signals 
            to an oncoming smart-car to stop.

MiddleSchoolOfEngineering
Author: Greg Yenney

*/

#include <SoftwareSerial.h>

const int myRx = 7;  // Shield: Rx=7, Tx=8
const int myTx = 8;  // Board:  Rx=4, Tx=2
const int myStopPin = 10;


char inputBuffer[256];

SoftwareSerial mySerial(myRx, myTx);

void setup()
{
  pinMode(myRx, INPUT_PULLUP);
  pinMode(myTx, OUTPUT);

  pinMode(myStopPin, OUTPUT);

  digitalWrite(myStopPin, LOW);

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
          SendMessage("Hello, from the SMS_car_controller!");
          break;

        default:
          break;
    }
  }


      
  if (mySerial.available()>0)
  {
      mySerial.readBytes(inputBuffer, 255);

      // print the original data that came in from the txt.
      //
      Serial.println();
      Serial.println("ORIGINAL_DATA: ");
      Serial.write(inputBuffer);
      Serial.println("ORIGINAL_DATA_END");

      // send the message to processTxt function which will read the txt to determine info:
      //    The phone number of sender 
      //    The txt message itself
      // processTxt gets the message in order to determine action for car.
      // 
      processTxt(inputBuffer, sizeof(inputBuffer));
  }   

  for (int j = 0 ; j < 256 ; j++)
  {
      inputBuffer[j] = 0;
  }
}

void SendMessage(String message)
{
  Serial.println("SendMessage()");
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(100);  // Delay of 1000 milli seconds = 1 second
  mySerial.println("AT+CMGS=\"phone_number_goes_here\"\r"); // Replace x with mobile number
  delay(100);
  mySerial.print("<Car_Controller_Message=");// The SMS text you want to send
  delay(100);
  mySerial.print(message);
  delay(100);
  mySerial.println(">");
  mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(100);
}

//void processTxt (String buffer, int buffsize, char * messageBuffer, int msgsize)
void processTxt (String buffer, int buffsize)
{
    Serial.println("In processTxt");
 
    //Serial.println(buffer);

    // Txt Format from Phone:  
    //
    // +CMT: "+18057270090","","16/03/15,23:57:58-28"
    // This is a multi-line txt message.  
    // Second line is here.
    // Txt ends on this line.
    //
    // NOTE: There is a blank line at the end.
    
    
    // Txt Format from email txt:
    //
    // +CMT: "1410100007","","16/03/16,00:01:34-28"
    //
    // FRM:middleschoolengineer1@gmail.com
    // MSG:Hello, From python!
    // This is a multi-line txt message.
    // 
    // NOTE:  There is a blank line at the end.

    String numberPreamble = "+CMT: \"";
    String message;
    String listenerPhonePrefix = "ListenerPhoneNumber=";

    // Get the phone number of the txt sender.
    //
    int senderNumBegin = buffer.indexOf(numberPreamble) + numberPreamble.length();   
    int senderNumEnd = buffer.indexOf("\",", senderNumBegin);
    String senderNumber = buffer.substring(senderNumBegin, senderNumEnd);
    Serial.print("Phone Number: ");  
    Serial.println(senderNumber);

    // Get the message itself
    //
    int messageBegin = buffer.indexOf("\n", senderNumEnd) + 1;
    message = buffer.substring(messageBegin, buffer.length() - 1);
    Serial.println("TXT Message: ");
    Serial.println(message);

    String stopMessage = "STOP";

    if (buffer.indexOf(stopMessage) > 0 )
    {
        Serial.println("Message is Stop!");  
        // send emergency stop signal here.
        digitalWrite(myStopPin, HIGH);
        delay(10000);
        digitalWrite(myStopPin, LOW);
    }
    else
    {
        Serial.println("Message is unhandled!");
    }
     
    Serial.println("returning from processTxt");
}


