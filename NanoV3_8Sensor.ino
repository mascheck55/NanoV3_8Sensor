#include <Arduino.h>

#include "LC_Sensor_Wire.h" //defines if sensor uses I2C
#include "LC_Sensor.h"

LC_Sensor mysensor = LC_Sensor(); // Instance of a sensor
#define D7 7
#define D8 8
#define SENSOR_BIT_D7 4
#define SENSOR_BIT_D8 5
byte sens;
byte v;
bool i;

#ifdef LC_SENSOR_USE_WIRE
// ============================================================================
// WIRE CONFIGURATION A4(SDA) A5(SCL) should work like a read only PCF8574
// any write command or output from DCC-EX will be ignored - no feedback
// ============================================================================
#include <Wire.h>
#pragma message "using Wire"
#define WIRE Wire

#define I2C_ADDRESS 0x65
void requestEvent() { WIRE.write(v); }
void receiveEvent(int howMany)
{
  while (WIRE.available())
    WIRE.read();
} // drop everything what is comming}
#endif

void setup()
{
  // put your setup code here, to run once:
  v = 0xFF; // all sensors shown as inactive

#if defined(LC_SENSOR_USE_WIRE)
  WIRE.begin(I2C_ADDRESS);
  WIRE.onRequest(requestEvent);
  WIRE.onReceive(receiveEvent);
#endif
  Serial.begin(115200);

  pinMode(D7, INPUT);
  pinMode(D8, INPUT);              // pullup will be ignored, plese use external pullup
  mysensor.begin(0, 100, 0, 0, 0); // works on A0
  delay(300);
  Serial.print("is Sensor running? ");
  if (mysensor.isRunning())
    Serial.println("yes");
  else
    Serial.println("no");
}

void loop()
{
  // there is no valid signal on A4 and A5 - because used for i2c
  // we use D7 and D8 as input for 2 x IR Sensor KY 032
  // if you use other signal like a button, please add external
  // pullup resistor since internals are all disabled.

  sens = mysensor.virtPort(); // get the LC Sensors, 
                              // the unused bits 4 and 5 are always 1=(not active)
  i = digitalRead(D7);
  if (!i)
    sens &= ~(1 << SENSOR_BIT_D7); // replaces A4
  i = digitalRead(D8);
  if (!i)
    sens &= ~(1 << SENSOR_BIT_D8); // replaces A5
  v = sens;                        // that is shown as "v" to i2c

  if (v != 0xFF) // Logic is like PCF8574 invers
  {
    Serial.print("0x");
    Serial.print(v, HEX);
    Serial.print("  ");

    for (int i = 7; i >= 0; i--)
    {
      Serial.print(bitRead(v, i));
    }

    Serial.println();
    delay(600);
  }
}
