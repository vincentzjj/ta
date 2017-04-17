#ifndef adcreader_h
#define adcreader_h

#include <Energia.h>
#include <SPI.h>

// MCP3008 channel addresses and instructions
const byte adcChannelAddresses[] =
{
  (0x08),                                // channel 0
  (0x09),                                // channel 1
  (0x0A),                                // channel 2  
  (0x0B),                                // channel 3             
  (0x0C),                                // channel 4             
  (0x0D),                                // channel 5             
  (0x0E),                                // channel 6             
  (0x0F)                                 // channel 7
};

class adcreader
{
  public:
    adcreader(int chipSelectPin);
    int begin();
    int read(int adcPin);
    int end();
  private:
    int _chipSelectPin;
    int _adcPin;
};

#endif // MCP3008_
