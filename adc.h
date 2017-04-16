#ifndef ADC_H
#define ADC_H

#define light_channel  0
#define temp_channel  1
#define delay 5

#define cspin 24
#define clockpin 23
#define Mmosipin 19
#define misopin 21

#include "Arduino.h"
#include "MCP3008.h"

MCP3008::MCP3008(int clockpin, int mosipin, int misopin, int cspin) {
    
    // define SPI outputs and inputs for bitbanging
    
    _cspin = cspin;
    _clockpin = clockpin;
    _mosipin = mosipin;
    _misopin = misopin;
    
    pinMode(_cspin, OUTPUT);
    pinMode(_clockpin, OUTPUT);
    pinMode(_mosipin, OUTPUT);
    pinMode(_misopin, INPUT);
    
}

// read SPI data from MCP3008 chip, 8 possible adc's (0 thru 7)
int MCP3008::readADC(int adcnum) {

  if ((adcnum > 7) || (adcnum < 0)) return -1; // Wrong adc address return -1

  // algo
  digitalWrite(_cspin, HIGH);

  digitalWrite(_clockpin, LOW); //  # start clock low
  digitalWrite(_cspin, LOW); //     # bring CS low

  int commandout = adcnum;
  commandout |= 0x18; //  # start bit + single-ended bit
  commandout <<= 3; //    # we only need to send 5 bits here
 
  for (int i=0; i<5; i++) {
    if (commandout & 0x80) 
      digitalWrite(_mosipin, HIGH);
    else   
      digitalWrite(_mosipin, LOW);
      
    commandout <<= 1;
    digitalWrite(_clockpin, HIGH);
    digitalWrite(_clockpin, LOW);

  }

  int adcout = 0;
  // read in one empty bit, one null bit and 10 ADC bits
  for (int i=0; i<12; i++) {
    digitalWrite(_clockpin, HIGH);
    digitalWrite(_clockpin, LOW);
    adcout <<= 1;
    if (digitalRead(_misopin))
      adcout |= 0x1;
  } 
  digitalWrite(_cspin, HIGH);

  adcout >>= 1; //      # first bit is 'null' so drop it
  return adcout;
}


 float ConvertVolts(adcout,places)
 {
   volts = (adcout * 3.3) / float(1023);
  volts = round(volts,places);
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
 
float ConvertTemp(adcout,places)
 {
  temp = ((adcout * 330)/float(1023))-50;
  temp = round(temp,places);
  return temp;
 } 
 

 
void main()
{
    
  MCP3008 adc(CLOCK_PIN, MOSI_PIN, MISO_PIN, CS_PIN);
while (1)
 {
   //Read the light sensor data
  light_level = adc.readADC(light_channel);
  light_volts = ConvertVolts(light_level,2);
 
  // Read the temperature sensor data
  temp_level = adc.readADC (temp_channel);
  temp_volts = ConvertVolts(temp_level,2);
  temp       = ConvertTemp(temp_level,2);
 
 
  // Wait before repeating loop
  time.sleep(delay);
  }
  }

#endif
