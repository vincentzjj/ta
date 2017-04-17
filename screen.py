#!C:\Python27\python.exe
 2 # -*- coding:UTF-8 -*-
 3 
 4 import Tkinter
 5 
 6 def center_window(w = 300, h = 200):
 7     ws = root.winfo_screenwidth()
 8     hs = root.winfo_screenheight()
 9     x = (ws/2) - (w/2)
10     y = (hs/2) - (h/2)
11     root.geometry("%dx%d+%d+%d" % (w, h, x, y))
12 
13 root = Tkinter.Tk(className='python gui')
14 center_window(500, 300)
15 root.mainloop()
