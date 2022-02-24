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

  Serial.begin(9600);
  Serial.println("Arduino Program Started");

}

void loop()
{
  
  // Check if should transmit
  checkTransmissionState();

  // Sample and Transmit if needed
  if(transmit)
  {
    // Send data on analog pin
    byte to_send[2];
    
    // Read Analog Pin
    uint16_t read_pin = analogRead(analogPIN);

    // Break up transmission into 2 byte segemtns
    // Send with MSB First (Upper byte)
    to_send[0] = (0xFF00 & read_pin) >> 8;
    to_send[1] = 0x00FF & read_pin;

    // Print the output to serial monitor (optional)
    Serial.println(to_send[0]);
    Serial.println(to_send[1]);

    // Write the bit array
    HM10.write(to_send, 2);

    // Set up delay time (1/f) - 4ms for 250Hz
    delay(5);
    //delay(500);
  }
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
