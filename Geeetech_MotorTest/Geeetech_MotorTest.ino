/*
STEM Center USA, Inc.
Pi-Bot: Motor Test Program using Function Calls
*/

#include <SoftwareSerial.h>

const int myRx = 7;  // Shield: Rx=7, Tx=8
const int myTx = 8;  // Board:  Rx=2, Tx=4

SoftwareSerial mySerial(myRx, myTx);

char inputBuffer[256];


const int In1 = 3;      
const int In2 = 5;      
const int In3 = 6;      
const int In4 = 11;  


String listenerPhone;
int processingMessage = 0;

void setup()
{
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
  
  mySerial.println("AT+IPR=19200");

  Serial.println ("Press \'s <enter>\' to Send a message and press \'r <enter>\' to receive a message.");

}
void loop()
{
  int speed1, speed2;
  int delayTime;
  speed1 = 150;
  speed2 = 150;
  while(1==1)
  {
    //delay(1000);
    //Serial.println("Starting loop()");
    
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
          case 'v':
            Serial.println("Make a Voice Call");
            SendVoiceCall();
            break;
          case 'c':
            Serial.println("sendATCIMI.");
            SendATCIMI();
            break;
            
          case 'i':
            Serial.println("GetInfo.");
            GetInfo();
            break;
          case 't':
            Serial.println("Get Time.");
            GetTime();
            break;
      }
    }
  
     
     if (mySerial.available()>0)
     {

        if (processingMessage == 0)
        {

           mySerial.readBytes(inputBuffer, 255);
           Serial.println("DATA: ");
           Serial.write(inputBuffer);
           Serial.println("DATA_DONE");
           processTxt(inputBuffer, sizeof(inputBuffer));
        }
        //int buffsize = sizeof(inputBuffer);
        //Serial.print("buff size: ");
        //Serial.println(buffsize);
        for (int i = 0 ; i < sizeof(inputBuffer) ; i++)
        {
            inputBuffer[i] = 0; // clear the buffer.
        }
        processingMessage = 0;

        
//        Serial.write(mySerial.read());
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
  }  
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
  mySerial.println("Hello, from Rover2.");// The SMS text you want to send
  delay(500);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(100);
  Serial.println("End SendMessage()");
}


void SendToListener(String listenerPhone)
{
  Serial.println("SendToListener()");
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  String sendMessagePhone = "AT+CMGS=\"" + listenerPhone + "\"\r";
  mySerial.println(sendMessagePhone);
  //mySerial.print("AT+CMGS=\"");
  //mySerial.print(listenerPhone);
  //mySerial.println("\"\r");
  
  //mySerial.println(sendMessagePhone); // Replace x with mobile number
  delay(1000);
  mySerial.println("This is a sent message from Rover2.");// The SMS text you want to send
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
 
 
void SendATCIMI()
{
  Serial.println("send_ATCIMI()");
  mySerial.println("AT+CIMI"); // AT Command to receive a live SMS
  delay(1000);
}
 
void SendVoiceCall()
{
  Serial.println("send_VoiceCall()");
  mySerial.println("ATD62418057270090"); // AT Command to receive a live SMS
  delay(1000);
}

void GetInfo()
{
   mySerial.println("AT+COPS?");
   delay(1000); 
   mySerial.println("AT+CSQ");
   delay(1000); 
   mySerial.println("ATI");
   delay(1000); 
   mySerial.println("AT+COPS?");
   delay(1000); 
   mySerial.println("AT+CGMR");
   delay(1000); 
   mySerial.println("AT+CREG");
   delay(1000); 
   mySerial.println("AT+CGMR");
   delay(1000); 
   
}

void GetTime()
{
   mySerial.println("AT+CLTS=");
   delay(1000);
}
 
void processTxt (String buffer, int buffsize)
{
    Serial.println("In processTxt");
 
    processingMessage = 1;
    
    //Serial.println(buffer);

    // Txt Format from Phone:  
    //
    // +CMT: "+18057270090","","16/03/15,23:57:58-28"
    // This is a multiline txt program.  
    // Beeline is here.
    // And another.
    //
    // NOTE: There is a blank line at the end.
    
    
    
    // +CMT: "1410100007","","16/03/16,00:01:34-28"
    //
    // FRM:middleschoolengineer1@gmail.com
    // MSG:Hello, From python!
    // This is a multi-line txt message.
    // 
    // NOTE:  There is a blank line at the end.

    String numberPreamble = "+CMT: \"";
    String emailFromPrefix = "FRM:";
    String emailMessagePrefix = "MSG:";
    int isFromEmail = 0;
    String emailAddress;
    String message;
    String listenerPhonePrefix = "ListenerPhoneNumber=";

    int senderNumBegin = buffer.indexOf(numberPreamble) + numberPreamble.length();   
    int senderNumEnd = buffer.indexOf("\",", senderNumBegin);
    String senderNumber = buffer.substring(senderNumBegin, senderNumEnd);
    Serial.print("Phone Number: ");  
    Serial.println(senderNumber);

    
    if (buffer.indexOf(emailFromPrefix) > 0)
    {
        isFromEmail = 1;
        int emailStart = buffer.indexOf(emailFromPrefix) + emailFromPrefix.length();
        int emailEnd =   buffer.indexOf("\n", emailStart);
        String emailAddress = buffer.substring(emailStart, emailEnd);
        Serial.print("Email Address: ");
        Serial.println(emailAddress);

        int messageBegin = buffer.indexOf(emailMessagePrefix, emailEnd) + emailMessagePrefix.length();
        int messageEnd = buffer.indexOf("\n\n", messageBegin);
        message = buffer.substring(messageBegin, messageEnd -1);
        Serial.println("Email Message: ");
        Serial.println(message);

        //if (message.indexOf(listenerPhonePrefix) > 0)
        if (message.indexOf(listenerPhonePrefix) >= 0)  // indexOf returns -1 if not found.
        {
              Serial.println("Found Listener Phone Prefix");
              int phoneBegin = message.indexOf(listenerPhonePrefix) + listenerPhonePrefix.length();
              int phoneEnd = message.indexOf("\n", phoneBegin);
              //listenerPhone = message.substring(phoneBegin, phoneBegin+9);
              listenerPhone = message.substring(phoneBegin, phoneEnd);
              Serial.print("Listener Phone Number: ");
              Serial.println(listenerPhone);
        }

        SendToListener(listenerPhone);

    }  else
    {
        int messageBegin = buffer.indexOf("\n", senderNumEnd) + 1;
        message = buffer.substring(messageBegin, buffer.length() - 1);
        Serial.println("TXT Message: ");
        Serial.println(message);
   }


        

    //Serial.println(buffer);
    Serial.println("returning from processTxt");
}
 
