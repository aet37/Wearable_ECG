// Code to read analog inputs into Arduino ATMEGA328P
/*
 * @author Andrew Toader
 * @date 02.16.2022
 * 
 */

#include <SoftwareSerial.h>

// Decalre Bueltooth transmission variables and functions
SoftwareSerial HM10(8, 9);  //RX = 0, TX = 1
bool transmit = false;
void checkTransmissionState(void);

// Declare Analog pin
int analogPIN = A0;

// LED PIN
int ledPIN = 2;

// BAUD Rate of tranmission
int BOD_R = 9600;


void setup()
{
  // Set debug PIN
  pinMode(ledPIN, OUTPUT);
  digitalWrite(ledPIN, LOW);

  // Set BT module BOD rate
  HM10.begin(BOD_R);

}

void loop()
{
  
  // Check if should transmit
  checkTransmissionState();

  // Sample and Transmit if needed
  if(transmit)
  {
    // Send data on analog pin
    HM10.write(analogRead(analogPIN));

    // Set up delay time (1/f) - 4ms for 250Hz
    delay(4);
    //delay(100);
  }
  
  /*
  // Send BT message over Serial Ports if transmit is true
    for(int i = 0; i < 10; i++)
    {
      checkTransmissionState();
      if(transmit == true)
      {
        HM10.write(i);
        delay(500);
      }
    }
    */

}

void checkTransmissionState()
{
  // Check if state of tranmist changed from master
  while(HM10.available() > 0)
  {
    int state = HM10.read();
    // Read state recieved
    // 8 => Start Transmission
    // 0 => Stop Transmission
    printf("%d", HM10.available());
    if(state == 8)
    {
      transmit = true;
      
      // Light LED
      digitalWrite(ledPIN, HIGH);
    }
    else
    {
      transmit = false;

      // Disable LED
      digitalWrite(ledPIN, LOW);
    }
  }
}
