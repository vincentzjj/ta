#include <Energia.h>
#include <SPI.h>
#include "adcreader.h"

// Instantiate with the chip select pin as an argument
// ----------------------------------------------------------------------------------------------
adcreader::adcreader(int chipSelectPin)
{
  _chipSelectPin = chipSelectPin;
}

// Call once to initialize
// ----------------------------------------------------------------------------------------------
int MCP3008::begin()
{
  SPI.setClockDivider(SPI_CLOCK_DIV8 );             // slow the SPI bus down
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);   
  SPI.begin();
  pinMode(_chipSelectPin, OUTPUT);
  digitalWrite(_chipSelectPin, LOW);                // Cycle the ADC CS pin on start per datasheet
  digitalWrite(_chipSelectPin, HIGH);
  return 0;
}

// Call whenever an analog to digital conversion is required with the pin number on the MCP3008
// as an argument.  Returns the integer digital value (10 bit value between 0 and 1023).
// ----------------------------------------------------------------------------------------------
int adcreader::read(int adcPin)
{
  _adcPin = adcPin;
  if ((_adcPin < 1) || (_adcPin > 8))                 // check for invalid pins
  {
    return -1;                                      // invalid pin
  }
  
  // The corresponding channel is one less than the pin number and the MCP3008 address and instructions
  // are stored in the array adcChannelAddresses
  byte channelAddress = adcChannelAddresses[_adcPin - 1]; 
  
  int adcValue = 0;
  byte MSB = 0x00; 
  byte LSB = 0x00;
  byte doNotCare = 0x00;                            // "don't care" byte
  
  digitalWrite(_chipSelectPin, LOW);
  SPI.transfer(0x01);                               // start Bit
  MSB = SPI.transfer(channelAddress << 4);          // send channel address/instruction and receive MSB,
  MSB = MSB & 0x03;                                 // mask the MSB to two bits
  LSB = SPI.transfer(doNotCare);                    // Send don't care and receive LSB byte in return
  digitalWrite(_chipSelectPin, HIGH); 

  return MSB << 8 | LSB;                            // Combine bytes and return 10 bit ADC value
}

// Call to bring SPI to an end.  Call MCP.begin() to start it up again.
// ----------------------------------------------------------------------------------------------
int adcreader::end()
{
  SPI.end();
  return 0;
}
