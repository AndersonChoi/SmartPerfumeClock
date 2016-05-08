#include <NS_Rainbow.h>
#include <VirtualWire.h>

#define N_CELL 8

const int ledPin = 10;
const int rfPin = 11;
const int Relay = 12;
const int Relay2 = 13;
boolean rfSignalIn=false;
NS_Rainbow ledStick = NS_Rainbow(N_CELL,ledPin);

byte message[VW_MAX_MESSAGE_LEN]; // a buffer to store the incoming messages
byte messageLength = VW_MAX_MESSAGE_LEN; // the size of the message

void setup()
{
  Serial.begin(9600);
  ledStick.begin();
  showNormalLED();
  delay(500);
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
    showLed(1,4);
    rfSignalIn=false;
    showNormalLED();
    delay(10);
    

  }


  delay(10);
  

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

void showLed(int color,int count)
{
  int r=200;
  int g=10;
  int b=20;

  if(color=1){
    r=20;
    g=10;
    b=250;
  }
  
  int bright=100;
  int brightDelay=100;

  for(int i=0;i<count;i++)
  {
        ledStick.clear();
        ledStick.setBrightness(bright); 
        ledStick.setColor(0,   r, g, b);
        ledStick.setColor(1,   r, g, b);
        ledStick.setColor(2,   r, g, b);
        ledStick.setColor(3,   r, g, b);
        ledStick.setColor(4,   r, g, b);
        ledStick.setColor(5,   r, g, b);
        ledStick.setColor(6,   r, g, b);
        ledStick.setColor(7,   r, g, b);
        ledStick.show();
        delay(brightDelay);
        ledStick.clear();
        ledStick.show();
        delay(brightDelay);
  }
  
  ledStick.clear();
}

void showNormalLED(){

  int bright=130;
  int r=10;
  int b=10;
  int g=10;
  ledStick.clear();
  ledStick.setBrightness(bright); 
  ledStick.setColor(0,   r, g, b);
  ledStick.setColor(1,   r, g, b);
  ledStick.setColor(2,   r, g, b);
  ledStick.setColor(3,   r, g, b);
  ledStick.setColor(4,   r, g, b);
  ledStick.setColor(5,   r, g, b);
  ledStick.setColor(6,   r, g, b);
  ledStick.setColor(7,   r, g, b);
  ledStick.show();
  
}

