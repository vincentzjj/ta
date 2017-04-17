#include "mcp3008Spi.h"
#include "ADCreader.h"
 
using namespace std;
mcp3008Spi a2d("/dev/spidev0.0", SPI_MODE_0, 1000000, 8);
    
     

     int a2dVal1 = 0;
     int a2dChannel1 = 0;
        unsigned char data1[3];
     float voltage1 = 0;
   void ADCreader::run()
   {
    running = true;
    while(running)
    {
        
     
        data1[0] = 1;  //  first byte transmitted -> start bit
        data1[1] = 0b10010000 |( ((a2dChannel1 & 7) << 4)); // second byte transmitted -> (SGL/DIF = 1, D2=D1=D0=0)
        data1[2] = 0; // third byte transmitted....don't care
 
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
      
     a2d.spiWriteRead(data1, sizeof(data1) );
 
        a2dVal1 = (data1[1]<< 8) & 0b1100100000; //merge data[1] & data[2] to get result
        a2dVal1 |=  (data1[2] & 0xff);
        voltage1 =((a2dVal1*330)/float(1023))-50;
       
    }
    
}    

 
float ADCreader::Data1()
 {
  output1 = voltage1;
  return output1;
 } 
 

 

