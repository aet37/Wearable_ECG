#include <SoftwareSerial.h>

SoftwareSerial HM10(8, 9);  //RX = 0, TX = 1
  
void setup()
{ 
  int BOD_R = 9600;

  // Set BT module BOD rate
  HM10.begin(BOD_R);
}

void loop()
{
  // Send BT message over Serial Ports
  for(int i = 0; i < 10; i++)
  {
    HM10.write(i);

    delay(100);
  }
  
}
