// Inluce the Serial module
#include <SoftwareSerial.h>

SoftwareSerial ble(8, 9);   // Rx = PIN2, Tx = PIN4

void setup()
{
  // Set up PIN8 as output pin
  pinMode(2, OUTPUT);
  
  // Open the serial port
  Serial.begin(9600);

  // Begin the BT LE connection
  ble.begin(9600);
}

void loop()
{
  // Send BT message
  for(int i = 0; i < 10; i++)
  {
    ble.write("Hi");
    digitalWrite(2, HIGH);
    delay(50);
    digitalWrite(2, LOW);
    
    delay(500);
  }
  
}
