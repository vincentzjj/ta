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
        float Data0();
        float Data1();
        float Data2();
private:
	bool running;
	float output0;
        float output1;
        float output2;
	

};

#endif
