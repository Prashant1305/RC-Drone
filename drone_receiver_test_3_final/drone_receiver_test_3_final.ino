/*
        DIY Arduino based RC Transmitter
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
Servo lefty;          //3
Servo leftx;        //5
Servo righty;      //6
Servo rightx;      //9
RF24 radio(7, 8);  // nRF24L01 (CE, CSN)
const byte address[6] = "00001"; // Address
// Max size of this struct is 32 bytes - NRF24L01 buffer limit
struct Data_PackageD {
  short j1PotX;
  short j1PotY;
  byte j1Button;
  short j2PotX;
  short j2PotY;
  byte j2Button;
  short pot1;
  short pot2;
  byte tSwitch1;
  byte tSwitch2;
  byte tSwitch3;
  byte tSwitch4;
  byte tSwitch5;
  byte tSwitch6;
};
Data_PackageD dataD; //Create a variable with the above structure
void setup() {
  Serial.begin(9600);
  // Define the radio communication
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
  leftx.attach(5);
  lefty.attach(3);
  rightx.attach(9);
  righty.attach(6);
}
void loop() {
  // Read all analog inputs and map them to one Byte value
  if (radio.available()) {
    radio.read(&dataD, sizeof(Data_PackageD));
    if (dataD.tSwitch1 == 1)
    {
      int j1x = dataD.j2PotY+1000;
      int j1y = dataD.j2PotX+1000;
      int j2x = dataD.j1PotY+1000;
      int j2y = dataD.j1PotX+1000;

      lefty.writeMicroseconds(j1y);
      leftx.writeMicroseconds(j1x);
      righty.writeMicroseconds(j2y);
      rightx.writeMicroseconds(j2x);

      Serial.print(" data.tSwitch4=");
      Serial.println(dataD.tSwitch4);
    }
  }
}
