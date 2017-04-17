import wx
  
def main():
  app = wx.App()
  win = wx.Frame(None,title='NotePad',size=(440,320))
  #很明显，title就是标题，size就是大小
  
  bt_open = wx.Button(win,label='open',pos=(275,2),size=(80,30))
  bt_save = wx.Button(win,label='save',pos=(355,2),size=(80,30))
  #label就是按钮显示的标签，pos是控件左上角的相对位置，size就是控件的绝对大小
  
  text_title = wx.TextCtrl(win,pos=(5,2),size=(265,30))
  text_content = wx.TextCtrl(win,pos=(5,34),size=(430,276),style=wx.TE_MULTILINE|wx.HSCROLL)
  #style样式，wx.TE_MULTILINE使其能够多行输入，wx.HSCROOL使其具有水平滚动条
  
  win.Show()
  app.MainLoop()
  
if __name__ == '__main__':
  main()
