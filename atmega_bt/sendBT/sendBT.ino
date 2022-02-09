#include <SoftwareSerial.h>

SoftwareSerial HM10(8, 9);  //RX = 0, TX = 1
bool transmit = false;
void checkTransmissionState(void);
  
void setup()
{ 
  // Set debug PIN
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  
  // BAUD Rate of tranmission
  int BOD_R = 9600;

  // Set BT module BOD rate
  HM10.begin(BOD_R);
}

void loop()
{
  checkTransmissionState();
  
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
      digitalWrite(2, HIGH);
    }
    else
    {
      transmit = false;

      // Disable LED
      digitalWrite(2, LOW);
    }
  }
}
