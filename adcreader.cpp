/***********************************************************************
 * mcp3008SpiTest.cpp. Sample program that tests the mcp3008Spi class.
 * an mcp3008Spi class object (a2d) is created. the a2d object is instantiated
 * using the overloaded constructor. which opens the spidev0.0 device with
 * SPI_MODE_0 (MODE 0) (defined in linux/spi/spidev.h), speed = 1MHz &
 * bitsPerWord=8.
 *
 * call the spiWriteRead function on the a2d object 20 times. Each time make sure
 * that conversion is configured for single ended conversion on CH0
 * i.e. transmit ->  byte1 = 0b00000001 (start bit)
 *                   byte2 = 0b1000000  (SGL/DIF = 1, D2=D1=D0=0)
 *                   byte3 = 0b00000000  (Don't care)
 *      receive  ->  byte1 = junk
 *                   byte2 = junk + b8 + b9
 *                   byte3 = b7 - b0
 *    
 * after conversion must merge data[1] and data[2] to get final result
 *
 *
 *
 * *********************************************************************/
#include "mcp3008Spi.h"
 
using namespace std;

int readadc(int Channel)
{
    mcp3008Spi a2d("/dev/spidev0.0", SPI_MODE_0, 1000000, 8);
    int i = 20;
       int a2dval = 0;
    
        unsigned char data[3];
 
    while(i > 0)
    {
        data[0] = 1;  //  first byte transmitted -> start bit
        data[1] = 0b10000000 |( ((Channel & 7) << 4)); // second byte transmitted -> (SGL/DIF = 1, D2=D1=D0=0)
        data[2] = 0; // third byte transmitted....don't care
 
        a2d.spiWriteRead(data, sizeof(data) );
 
        a2dval = 0;
                a2dval = (data[1]<< 8) & 0b1100000000; //merge data[1] & data[2] to get result
                a2dval |=  (data[2] & 0xff);
        sleep(1);
        i--;
    }
    return a2dval ;
}    

  float round(float number)
{
    return (number > 0.0) ? (number + 0.5) : (number - 0.5); 
}

 float ConvertVolts(int adcout)
 {
    float volts; 
   volts = (adcout * 3.3) / float(1023);
  volts = round(volts);
  return volts;
 }
  
  /* ADC Value
   (approx)  Temp  Volts
     0      -50    0.00
     78      -25    0.25
    155        0    0.50
    233       25    0.75
    310       50    1.00
    465      100    1.50
    775      200    2.50
   1023      280    3.30 */
 
float ConvertTemp(int adcout)
 {
   float temp;  
  temp = ((adcout * 330)/float(1023))-50;
  temp = round(temp);
  return temp;
 } 
 

 
float read()
{
    
while (1)
 {int light_channel=0;
   int temp_channel=1;
  int delay=2;
   int light_level,temp_level;
   float light_volts,temp_volts,temp;
     
   //Read the light sensor data
  light_level = readadc(light_channel);
  light_volts = ConvertVolts(light_level);
 
  // Read the temperature sensor data
  temp_level = readadc(temp_channel);
  temp_volts = ConvertVolts(temp_level);
  temp       = ConvertTemp(temp_level);
 
  // Wait before repeating loop
  time.sleep(delay);}
 
 return temp;
}
