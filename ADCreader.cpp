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
#include "ADCreader.h"
 
using namespace std;
mcp3008Spi a2d("/dev/spidev0.0", SPI_MODE_0, 1000000, 8);
    
     int a2dVal0 = 0;
     int a2dChannel0 = 0;
        unsigned char data0[3];
     float voltage0 = 0;

     int a2dVal1 = 0;
     int a2dChannel1 = 0;
        unsigned char data1[3];
     float voltage1 = 0;
   void ADCreader::run()
   {
    running = true;
    while(running)
    {
        data0[0] = 1;  //  first byte transmitted -> start bit
        data0[1] = 0b10000000 |( ((a2dChannel0 & 7) << 4)); // second byte transmitted -> (SGL/DIF = 1, D2=D1=D0=0)
        data0[2] = 0; // third byte transmitted....don't care
     
        data1[0] = 1;  //  first byte transmitted -> start bit
        data1[1] = 0b10010000 |( ((a2dChannel1 & 7) << 4)); // second byte transmitted -> (SGL/DIF = 1, D2=D1=D0=0)
        data1[2] = 0; // third byte transmitted....don't care
 
        a2d.spiWriteRead(data0, sizeof(data0) );
 
        a2dVal0 = 0;
        a2dVal0 = (data0[1]<< 8) & 0b1100000000; //merge data[1] & data[2] to get result
        a2dVal0 |=  (data0[2] & 0xff);
        voltage0 = (a2dVal0*3.3)/float(1023);
      
     a2d.spiWriteRead(data1, sizeof(data1) );
 
        a2dVal1 = 0;
        a2dVal1 = (data1[1]<< 8) & 0b1100000000; //merge data[1] & data[2] to get result
        a2dVal1 |=  (data1[2] & 0xff);
        voltage1 =((a2dVal1*330)/float(1023))-50;
       
    }
    
}    

 
 float ADCreader::Data0()
 {
     
   output0 = voltage0;

  return output0;
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
 
float ADCreader::Data1()
 {
  output1 = voltage1;
  return output1;
 } 
 

 

