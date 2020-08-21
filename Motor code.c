#include <SPI.h>
#include "mcp_can.h"
#define can_id 1522                              // defines can id as 1522
#define inPin A3
const int SPI_CS_PIN = 9;
MCP_CAN CAN(SPI_CS_PIN);                         // Set CS pin

int in1 = 4;
int in2 = 5;
int pwm = 6;
int in = 0;
float temperature = 0;

//PROBLEM START//

double GetReading(){
  unsigned char incomingMessageData[8];
  

  reading = 0.0;
 
  //appends an array in binary
  reading = (incomingMessageData[6or7] << 8 | incomingMessageData[7or8])/100.0;

  //TODO:
  //test the math
  //
  //a double array with 8 elements holds the information.
  //the array is read from where?
  //Check if there is a CAN message available on the bus
  if(CAN_MSGAVAIL == CAN.checkRecieve()){


  }



  reading = (((byte6)<<8 | byte7)/100.0);

  return reading;
}

// TO DO: add function for appending the two 8 bit long binary numbers.
//canbus_reading = (((byte6)<<8 | byte7)/100.0);  This moves byte6 8 bits to the left to make way for byte7. MUST INCLUDE IN CODE.
//Make an array to store data from all the bytes. For this function, we only care about bytes 6&7. Check examples in canbus library. 

//PROBLEM END//



//double TemperatureConverter
//Parameters: double canbus_reading (the reading outputed by canbus).
//Purpose: Converts the canbus reading into a value between 0-255.

double TemperatureConverter (double canbus_reading){
  double converted = 255.0*(canbus_reading/187.0);  // converts the value outputed by canbus between 0-255
  
   if(converted < 249.54){                          // if the value outputed by the canbus is less than 183F i.e 249.54 after conversion.
    return 0.0;
  }
 
  else if(converted > 249.54 && converted < 255.0){
    double x = canbus_reading;
    x-183.0;
    return (x*56.1+30.6);                          //y=mx+b, m=56.1, b=30.6 i.e. 12% of 255.
  }

  else if(converted >= 255.0){                    // if the value outputed by canbus exceeds 187F i.e 255 after conversion.                  
    return 255.0;                           
  }
 
  return 0.0;
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
pinMode(pwm, OUTPUT);
pinMode(in1, OUTPUT);
pinMode(in2, OUTPUT);
pinMode(A3, INPUT);

  
//canbus stuff, block of code required to setup every canbus by default. DO NOT CHANGE.
    while (CAN_OK != CAN.begin(CAN_500KBPS))              // init can bus : baudrate = 500k
    {
        Serial.println("CAN BUS Shield init fail");
        Serial.println(" Init CAN BUS Shield again");
        delay(100);
    }
    Serial.println("CAN BUS Shield init ok!");

}

void loop() {
  // put your main code here, to run repeatedly:

digitalWrite(in1,1) ;
digitalWrite(in2,0) ;
//analogWrite(pwm,0) ;
in = analogRead(inPin)/4;
Serial.println(in);
analogWrite(pwm,in) ;


}