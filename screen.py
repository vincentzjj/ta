import wx
  
def main():
  app = wx.App()
  win = wx.Frame(None,title='NotePad',size=(440,320))
  
  
  bt_open = wx.Button(win,label='open',pos=(275,2),size=(80,30))
  bt_save = wx.Button(win,label='save',pos=(355,2),size=(80,30))

  
  text_title = wx.TextCtrl(win,pos=(5,2),size=(265,30))
  text_content = wx.TextCtrl(win,pos=(5,34),size=(430,276),style=wx.TE_MULTILINE|wx.HSCROLL)

  
  win.Show()
  app.MainLoop()
  
if __name__ == '__main__':
  main()
