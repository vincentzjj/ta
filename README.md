                                                      Tenmperature alarm 
Team 6
We got 2 types of temperature sensor. 
The first one was written by python. It can show the temperature and also indicate the alarm on the screen with the time change. However, it can not be plotted the figure out. It started in the remote ssh session.
1.git clone https://github.com/vincentzjj/ta.git
2.$cd ta
3.python team6.py
The youtube Video link is below
https://www.youtube.com/watch?v=RW4Ff7xnhxM


The second one is to plot the detected temperature which is changing with the time. It can also show the temperature with the real time. It is writen in QT.Start it in the remote ssh session and it shows up on the RPI screen.
1.git clone https://github.com/vincentzjj/ta.git
2.$cd ta
3.$qmake
4.$make
5.$sudo startx ./Temp
Make sure that you have installed QT4 and qwt-dev which. If not then install it with the debian package management tools"apt-get" or "dselect".
The youtube Video link is below
https://www.youtube.com/watch?v=T5zhtI7FKzE
