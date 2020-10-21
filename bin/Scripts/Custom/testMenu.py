from Menu import Menu
from MenuManager import MenuManager
import win32gui,win32con
import win32api
from GUIUtility import GUIUtility

class testMenu(Menu):

    @Menu.MenuItem(path = '文件(&F)/保存(&S)',checkable = False,group = 0,pos = 0,shortcut = "CTRL+S")
    def action_SaveFile():
        path = GUIUtility.AskOpenFile("action_SaveFile")
        GUIUtility.MessageBox("show path",path)

    @Menu.MenuItem(path = '文件(&F)/读取(&S)',checkable = False,group = 0,pos = 1,shortcut = "CTRL+R")
    def action_ReadFile():
        path = GUIUtility.AskOpenFile("action_ReadFile")
        GUIUtility.MessageBox("show path",path)

    @Menu.MenuItem(path = '文件(&F)/另存为(&S)',checkable = False,group = 0,pos = 2,shortcut = "CTRL+SHIFT+O")
    def action_otherSaveFile():
        path = GUIUtility.AskOpenFile("action_otherSaveFile")
        GUIUtility.MessageBox("show path",path)

    @Menu.MenuItem(path = '文件(&F)/退出(&F)',checkable = False,group = 1,pos = 0,shortcut = "CTRL+Q")
    def action_quit():
        GUIUtility.MessageBox("Quit","aaaa")
 
    @Menu.MenuItem(path = '文件(&F)/某某(&F)',checkable = False,group = 1,pos = 0,shortcut = "CTRL+Q")
    def action_quit1():
        GUIUtility.MessageBox("Quit","aaaa")

    @Menu.MenuItem(path = '编辑(&E)/搜索(&S)',checkable = False,group = 0,pos = 0,shortcut = "CTRL+F")
    def action_find():
        GUIUtility.MessageBox("what do you want to find","aaaa")

    @Menu.MenuItem(path = '编辑(&E)/A/B',checkable = False,group = 0,pos = 0,shortcut = "CTRL+F")
    def action_find1():
        GUIUtility.MessageBox("what do you want to find","aaaa")