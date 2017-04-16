#ifndef adcreader_h
#define adcreader_h

#include "Arduino.h"

#include <QThread>

class ADCreader : public QThread

class adcreader
{
  public:
    adcreader(int clockpin, int mosipin, int misopin, int cspin);
    int readADC(int adcnum);
  private:
      int _clockpin, _mosipin, _misopin, _cspin;
};


#endif
