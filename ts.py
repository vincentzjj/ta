import spidev
import time
import os
import sys
# Open SPI bus
spi = spidev.SpiDev()
spi.open(0,0)

# Function to read SPI data from MCP3008 chip
# Channel must be an integer 0-7
def ReadChannel(channel):
  adc = spi.xfer2([1,(8+channel)<<4,0])
  data = ((adc[1]&3) << 8) + adc[2]
  return data

# Function to convert data to voltage level,
# rounded to specified number of decimal places. 
def ConvertVolts(data,places):
  volts = (data * 3.3) / float(1023)
  volts = round(volts,places)  
  return volts
  
# Function to calculate temperature from
# TMP36 data, rounded to specified
# number of decimal places.
def ConvertTemp(data,places):

  # ADC Value
  # (approx)  Temp  Volts
  #    0      -50    0.00
  #   78      -25    0.25
  #  155        0    0.50
  #  233       25    0.75
  #  310       50    1.00
  #  388       75    1.25
  #  465      100    1.50
  #  543      125    1.75
  #  620      150    2.00
  #  698      175    2.25
  #  775      200    2.50
  #  853      225    2.75
  #  930      250    3.00
  # 1008      275    3.25
  # 1023      280    3.30

  temp = ((data * 330)/float(1023))-50
  temp = round(temp,places)
  return temp
  
# Define sensor channels
light_channel = 0
temp_channel  = 1

# Define delay between readings
delay = 5

while True:

  # Read the light sensor data
  light_level = ReadChannel(light_channel)
  light_volts = ConvertVolts(light_level,2)

  # Read the temperature sensor data
  temp_level = ReadChannel(temp_channel)
  temp_volts = ConvertVolts(temp_level,2)
  temp       = ConvertTemp(temp_level,2)   

  
from PyQt4 import QtCore, QtGui  
try:
    _fromUtf8 = QtCore.QString.fromUtf8

except AttributeError:

    _fromUtf8 = lambda s: s

 

class Ui_ts(object):

    def setupUi(self, ts):

        ts.setObjectName(_fromUtf8("Temperature alarm"))

        ts.resize(304, 212)

        self.centralWidget = QtGui.QWidget(ts)

        self.centralWidget.setObjectName(_fromUtf8("centralWidget"))

        self.lcdTemp = QtGui.QLCDNumber(self.centralWidget)

        self.lcdTemp.setGeometry(QtCore.QRect(40, 40, 221, 81))

        self.lcdTemp.setSmallDecimalPoint(False)

        self.lcdTemp.setDigitCount(6)

        self.lcdTemp.setObjectName(_fromUtf8("lcdTemp"))

        self.sliderAlarm = QtGui.QSlider(self.centralWidget)

        self.sliderAlarm.setGeometry(QtCore.QRect(40, 170, 221, 16))

        self.sliderAlarm.setMaximum(120)

        self.sliderAlarm.setProperty("value", 80)

        self.sliderAlarm.setOrientation(QtCore.Qt.Horizontal)

        self.sliderAlarm.setTickPosition(QtGui.QSlider.NoTicks)

        self.sliderAlarm.setObjectName(_fromUtf8("sliderAlarm"))

        self.labelAlarm = QtGui.QLabel(self.centralWidget)

        self.labelAlarm.setGeometry(QtCore.QRect(40, 150, 221, 16))

        self.labelAlarm.setObjectName(_fromUtf8("labelAlarm"))

        self.labelTemp = QtGui.QLabel(self.centralWidget)

        self.labelTemp.setGeometry(QtCore.QRect(40, 20, 221, 16))

        self.labelTemp.setObjectName(_fromUtf8("labelTemp"))

       

        #Add timer

        self.timerTemp = QtCore.QTimer(self.centralWidget)       

        ts.setCentralWidget(self.centralWidget)       

       

        # Add slots

        self.sliderAlarm.valueChanged.connect(self.sliderAlarm_ValueChanged)

        self.timerTemp.timeout.connect(self.timerTemp_TimeOut)

        # Use the timeout event to initialize the LCD

        self.timerTemp_TimeOut()

        # Start timer, time out per 2 seconds

        self.timerTemp.start(2000)

       

       

        self.retranslateUi(ts)

        QtCore.QMetaObject.connectSlotsByName(ts)

                                       

 

    def retranslateUi(self, ts):

        ts.setWindowTitle(QtGui.QApplication.translate("ts", "ts", None, QtGui.QApplication.UnicodeUTF8))

        self.labelAlarm.setText(QtGui.QApplication.translate("ts", "Alarm: 80C", None, QtGui.QApplication.UnicodeUTF8))

        self.labelTemp.setText(QtGui.QApplication.translate("ts", "Temperature", None, QtGui.QApplication.UnicodeUTF8))

 

    # Event triggered when the value of labelAlarm changed

    def sliderAlarm_ValueChanged(self):

        self.labelAlarm.setText("Alarm: " + str(self.sliderAlarm.value()) + "C")

       

    # Event triggered when timerTemp time out

    def timerTemp_TimeOut(self):

        # Get temperature from sensor file

        sensor = temp

        t = float(sensor.readline()) / 1000

        alarm = float(self.sliderAlarm.value())

        # Display temperature

        self.lcdTemp.display("%.1fC" % temp)

        # Check whether the temperature is too high

        if t <= alarm * 0.6:

            self.lcdTemp.setStyleSheet("color: green")

        elif t <= alarm * 0.8:

            self.lcdTemp.setStyleSheet("color: orange")

        elif t <= alarm:

            self.lcdTemp.setStyleSheet("color: red")

        else:

            self.lcdTemp.setStyleSheet("color: red")

            msg = QtGui.QMessageBox()

            msg.setWindowTitle("Alarm")

            msg.setText("Temperature is too high!")

            msg.setIcon(QtGui.QMessageBox.Warning)

            msg.exec_()

         

           

if __name__ == "__main__":

    import sys

    app = QtGui.QApplication(sys.argv)

    ts = QtGui.QMainWindow()

    ui = Ui_ts()

    ui.setupUi(ts)

    ts.show()

sys.exit(app.exec_())
