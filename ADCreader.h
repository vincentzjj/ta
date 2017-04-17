#ifndef ADCREADER
#define ADCREADER
#include "mcp3008Spi.h"
#include <QThread>

class ADCreader : public QThread
{
public:
	ADCreader() {running = 0;};
	void quit();
	void run();
        float Data1();
      
private:
	bool running;
        float output1;
       

};

#endif
