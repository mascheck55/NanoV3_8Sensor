#pragma once
#define LC_SENSOR_USE_WIRE
//the pins A4 and A5 will be marked as unused
/*
you may use the A4 as SCA and A5 as SCL now - do not 
forget the ground connection - GND

when connected to the DCC-EX as i2c device you may use the 
PCF8574 Driver as input driver inside DCC-EX
For this purpose include the following to the myAutomation.h file

HAL(PCF8574, 800,8,0x65)

hereby is 
       PCF8574 = driver name
       800     = your choice for the first virtual address
       8       = 8 bit, the driver has no more
       0x65    = the i2c address according to your program
*/
