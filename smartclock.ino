#include <VirtualWire.h>

const int rfPin = 11;
const int Relay = 12;
const int Relay2 = 13;
boolean rfSignalIn=false;

byte message[VW_MAX_MESSAGE_LEN]; // a buffer to store the incoming messages
byte messageLength = VW_MAX_MESSAGE_LEN; // the size of the message

void setup()
{
  Serial.begin(9600);
  vw_set_rx_pin(rfPin);
  vw_setup(2000); 
  vw_rx_start(); 
  pinMode(Relay, OUTPUT);     //Set Pin3 as output
  pinMode(Relay2, OUTPUT);     //Set Pin3 as output
}


void loop()
{


  if (vw_get_message(message, &messageLength)) // Non-blocking
  {
    Serial.print("Received: ");
    for (int i = 0; i < messageLength; i++)
    { 
      Serial.write(message[i]);
      if(message[i]==49)// 49byte == "1"
      {
        rfSignalIn=true;
      }
    }
    
    Serial.println();
  }

  if(rfSignalIn)
  {
    Serial.println("pump01 is active@!");
    pumpActive01();
    rfSignalIn=false;
  }


  

}

void pumpActive01(){
          digitalWrite(Relay, HIGH);   //Turn off relay
          delay(170);
          digitalWrite(Relay, LOW);    //Turn on relay
         

}

void pumpActive02(){
          digitalWrite(Relay2, HIGH);   //Turn off relay
          delay(170);
          digitalWrite(Relay2, LOW);    //Turn on relay
          

}

