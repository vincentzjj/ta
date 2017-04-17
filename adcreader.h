#ifndef ADCREADER
#define ADCREADER

#include <QThread>

class ADCreader : public QThread
{
public:
	ADCreader() {running = 0;};
	void quit();
	int run(int Channel);
	float round(float number);
	float ConvertVolts(int adcout);
	float ConvertTemp(int adcout);
	float read();
private:
	bool running;
	

};

#endif
