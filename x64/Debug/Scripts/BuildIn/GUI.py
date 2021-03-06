from abc import ABC,abstractmethod
import functools
import win32gui,win32con
import win32api
import uuid
import os
import sys
from Debug import Debug
from GUIUtility import GUIUtility
import qt_module_wrapped

# 窗口类型 定义
class WidgetType():
     Button = 0
     Label = 1
     LineEdit = 2
     Spacer = 3
     HLayout = 4
     VLayout = 5
     EndLayout = 6
     CheckBox = 7
     ProgressBar = 8
     BeginGroup = 9
     EndGroup = 10
     IPAddress = 11
     ComboBox = 12
     TableView = 13

# 事件 类型 定义
class EventType():
     Button_Click = 0
     Edit_Finished = 1
     CheckState_Changed = 2
     ComboBox_Index_Changed = 3
     TableView_Selection_Chanced = 4


# C++调用类
# 窗口信息，包含了窗口的类型名称，窗口及其控件的句柄

class WidgetInfo(object):
    # 构造函数 参数包含，窗口句柄，以及窗口类型名称
    def __init__(self,ptr,widgetClassName):
        self.widgetClassName = widgetClassName
        self.handleMap = {}
        self.ptr = ptr

    # 添加句柄，参数为句柄对象名，句柄指针
    def addHandle(self,handleName,handleType,handlePtr):
        self.handleMap[handleName] = (handleType,handlePtr)

    # 根据句柄名称返回句柄指针
    def findHandle(self,handleName):
        if handleName not in self.handleMap:
            return None
        else:
            handlePair = self.handleMap[handleName]
            type = handlePair[0]
            ptr = handlePair[1]
            return ptr

# 窗口事件 信息（由@GUI.Slot 调用后添加）
class WidgetEventInfo(object):
    def __init__(self):
        # 事件字典：key:接收者对象 value:槽函数名称
        self.objectEventMap = {}
    
    #添加事件
    def addEvent(self,receiver,eventType,slotName):
        self.objectEventMap[receiver] = (eventType,slotName)

    #根据 接收者对象 获取 槽函数名称
    def getEvent(self,receiver):
        if receiver not in self.objectEventMap:
            return None
        else:
            return self.objectEventMap[receiver]

# 构建窗口生成的描述信息，返回json值，供C++解析
class WidgetCommandBuilder():
    def __init__(self):
        self.commands = []
        self.jsonStr = None

    def doButton(self, objectName,buttonText):
        self.commands.append([WidgetType.Button,objectName,buttonText])

    def doLabel(self,text):
        self.commands.append([WidgetType.Label,text])

    def doLineEdit(self,objectName):
        self.commands.append([WidgetType.LineEdit,objectName])

    def doCheckBox(self,objectName,text,checked):
        self.commands.append([WidgetType.CheckBox,objectName,text,checked])

    def doProgressBar(self,objectName,value,min,max):
        self.commands.append([WidgetType.ProgressBar,objectName,value,min,max])

    def doHLayout(self):
        self.commands.append([WidgetType.HLayout])

    def doVLayout(self):
        self.commands.append([WidgetType.VLayout])

    def doEndLayout(self):
        self.commands.append([WidgetType.EndLayout])

    def doBeginGroup(self,groupName):
        self.commands.append([WidgetType.BeginGroup,groupName])

    def doEndGroup(self):
        self.commands.append([WidgetType.EndGroup])

    def doIPAddress(self,objectName):
        self.commands.append([WidgetType.IPAddress,objectName])

    def doSpacing(self,spacing):
        self.commands.append([WidgetType.Spacer,spacing])

    def doCombox(self,objectName:str,items:list):
        self.commands.append([WidgetType.ComboBox,objectName,items])

    def doTable(self,objectName:str,header:list):
        self.commands.append([WidgetType.TableView,objectName,header])

    def getJsonResult(self):
        if self.jsonStr != None:
            return self.jsonStr
        else:
            import json
            self.jsonStr =  json.dumps(self.commands)
            return self.jsonStr

# 所有窗口的基类
class Widget(ABC):
    def __init__(self):
        self.UUID = 0

    def getUUID(self):
        return self.UUID

    @abstractmethod
    def OnGUI(self):
        pass

    @abstractmethod
    def OnClose(self):
        pass

class GUI(object):

    # C++ 扫描 py文件时候调用

    #当前扫描的类
    CurrentWidgetClassName = None

    #当前的UI生成命令集
    CurrentWidgetCommands = None

    #当前的UI info指针
    CurrentWidgetInfo = None

    #当前窗口的UUID
    CurrentWidgetUUID = None

    # 字典：key = 窗口类名称，value = 窗口描数信息
    WidgetCommandsMaps = {}

    # 字典：key = 窗口类名称，value = 窗口事件 信息
    WidgetEventMap = {}
    
    # 字典：key = 窗口UUID ， value = 窗口信息类
    UUIDToWidgetMap = {}

    def RequireGUIBegin(func):
        def wrapper(*args,**kwarg):
            if not GUI.CurrentWidgetCommands:
                Debug.printWarning("you should call GUI.Begin(ptr) first")
                return
            func(*args,**kwarg)
        return wrapper

    @staticmethod
    @RequireGUIBegin
    def Button(buttonName,buttonText):
        GUI.CurrentWidgetCommands.doButton(buttonName,buttonText)

    @staticmethod
    @RequireGUIBegin
    def Label(text):
        GUI.CurrentWidgetCommands.doLabel(text)

    @staticmethod
    @RequireGUIBegin
    def BeginGroup(groupName):
        GUI.CurrentWidgetCommands.doBeginGroup(groupName)

    @staticmethod
    @RequireGUIBegin
    def EndGroup():
        GUI.CurrentWidgetCommands.doEndGroup()

    @staticmethod
    @RequireGUIBegin
    def LineEdit(objectName):
        GUI.CurrentWidgetCommands.doLineEdit(objectName)

    @staticmethod
    @RequireGUIBegin
    def CheckBox(objectName,text,checked = False):
        GUI.CurrentWidgetCommands.doCheckBox(objectName,text,checked)

    @staticmethod
    @RequireGUIBegin
    def Spacer(spacing:int):
        GUI.CurrentWidgetCommands.doSpacing(spacing)

    @staticmethod
    @RequireGUIBegin
    def ProgressBar(objectName,value = 0,min = 0,max = 100):
        GUI.CurrentWidgetCommands.doProgressBar(objectName,value,min,max)

    @staticmethod
    @RequireGUIBegin
    def IPAddress(objectName):
        GUI.CurrentWidgetCommands.doIPAddress(objectName)

    @staticmethod
    @RequireGUIBegin
    def Table(objectName,header):
        GUI.CurrentWidgetCommands.doTable(objectName,header)

    @staticmethod
    @RequireGUIBegin
    def ComboBox(objectName,items):
        GUI.CurrentWidgetCommands.doCombox(objectName,items)

    @staticmethod
    def Slot(receiver,eventType):
        if GUI.CurrentWidgetClassName not in GUI.WidgetEventMap:
            GUI.WidgetEventMap[GUI.CurrentWidgetClassName] = WidgetEventInfo()
        def decorator(func):
            GUI.WidgetEventMap[GUI.CurrentWidgetClassName].addEvent(receiver,eventType,func.__name__)
            @functools.wraps(func)
            def wrapper(*args, **kwargs):
                return func(*args, **kwargs)
            return wrapper
        return decorator
    
    @staticmethod
    def InvokeButtonClickShot(objectName):
        info = GUI.UUIDToWidgetMap[GUI.CurrentWidgetUUID]
        eventName = GUI.WidgetEventMap[info.widgetClassName].getEvent(objectName)[1]
        if(not eventName):
            return
        function = getattr(info.ptr,eventName)
        if(function != None):
            function()

    @staticmethod
    def InvokeEditFinishedShot(objectName):
        info = GUI.UUIDToWidgetMap[GUI.CurrentWidgetUUID]
        eventName = GUI.WidgetEventMap[info.widgetClassName].getEvent(objectName)[1]
        if(not eventName):
            return
        function = getattr(info.ptr,eventName)
        if(function != None):
            function()

    @staticmethod
    def InvokeCheckStateChangedShot(objectName):
        info = GUI.UUIDToWidgetMap[GUI.CurrentWidgetUUID]
        eventName = GUI.WidgetEventMap[info.widgetClassName].getEvent(objectName)[1]
        if(not eventName):
            return
        function = getattr(info.ptr,eventName)
        if(function != None):
           function()

    @staticmethod
    def InvokeComboBoxIndexChangedShot(objectName):
        info = GUI.UUIDToWidgetMap[GUI.CurrentWidgetUUID]
        eventName = GUI.WidgetEventMap[info.widgetClassName].getEvent(objectName)[1]
        if(not eventName):
            return
        function = getattr(info.ptr,eventName)
        if(function != None):
           function()

    @staticmethod
    def InvokeTableViewSelectionChangedShot(objectName):
        info = GUI.UUIDToWidgetMap[GUI.CurrentWidgetUUID]
        eventName = GUI.WidgetEventMap[info.widgetClassName].getEvent(objectName)[1]
        if(not eventName):
            return
        function = getattr(info.ptr,eventName)
        if(function != None):
           function()

    @staticmethod
    def BeginGUI(ptr):
        #生成 当前窗口的 UUID
        ptr.UUID = str(uuid.uuid1())
        #设置当前的 指针
        GUI.CurrentWidgetPtr = ptr
        #获取窗口类名
        className = GUI.CurrentWidgetPtr.__class__.__name__
        GUI.CurrentWidgetCommands = WidgetCommandBuilder()
        GUI.CurrentWidgetInfo = GUI.UUIDToWidgetMap[ptr.UUID] = WidgetInfo(ptr,className)

    @staticmethod
    def EndGUI():
        className = GUI.CurrentWidgetPtr.__class__.__name__
        GUI.WidgetCommandsMaps[className] = GUI.CurrentWidgetCommands
        GUI.CurrentWidgetPtr = None
        GUI.CurrentWidgetCommands = None
        GUI.CurrentWidgetUUID = None

    @staticmethod
    def BeginHorizontalLayout():
        GUI.CurrentWidgetCommands.doHLayout()

    @staticmethod
    def BeginVerticalLayout():
        GUI.CurrentWidgetCommands.doVLayout()

    @staticmethod
    def EndLayout():
        GUI.CurrentWidgetCommands.doEndLayout()

    @staticmethod
    def GetUIElementsJsonString():
        string =  GUI.WidgetCommandsMaps[GUI.CurrentWidgetClassName].getJsonResult()
        return string
       
    @staticmethod
    def SetCurrentUUID(uuid):
        GUI.CurrentWidgetUUID = uuid

    @staticmethod
    def SetCurrentWidgetClassName(name):
        GUI.CurrentWidgetClassName = name

    @staticmethod
    def GetCurrentWidgetInfos():
        return GUI.CurrentWidgetInfo

    class set():
        @staticmethod
        def SetStyleSheet(self,objectName,qssStr):
            handle = GUI.UUIDToWidgetMap[self.getUUID()].findHandle(objectName)
            if not handle:
                Debug.printError(objectName+" not found")
            else:
                handle.setQss(qt_module_wrapped.qstr(qssStr))

        @staticmethod
        def SetProgressBarValue(self,objectName,value):
            handle = GUI.UUIDToWidgetMap[self.getUUID()].findHandle(objectName)
            if not handle:
                Debug.printError(objectName+" not found")
            else:
                handle.setValue(value)

        @staticmethod
        def SetLineEditText(self,objectName,text):
            ptr = GUI.UUIDToWidgetMap[self.getUUID()].ptr
            handle = GUI.UUIDToWidgetMap[self.getUUID()].findHandle(objectName)
            if not handle:
                Debug.printError(objectName+" not found")
            else:
                handle.setText(qt_module_wrapped.qstr(text))
   
        @staticmethod
        def SetControlEnabled(self,objectName,enabled:bool):
            handle = GUI.UUIDToWidgetMap[self.getUUID()].findHandle(objectName)
            if not handle:
                Debug.printError(objectName+" not found")
            else:
                handle.setEnabled(enabled)

        @staticmethod
        def SetIP(self,objectName,IP):
            handle = GUI.UUIDToWidgetMap[self.getUUID()].findHandle(objectName)
            if not handle:
                Debug.printError(objectName+" not found")
            else:
                handle.setIP(qt_module_wrapped.qstr(IP))

    class get():
        @staticmethod
        def GetProgressBarValue(self,objectName):
            handle = GUI.UUIDToWidgetMap[self.getUUID()].findHandle(objectName)
            return handle.getValue()

        @staticmethod
        def GetLineEditText(self,objectName):
            ptr = GUI.UUIDToWidgetMap[self.getUUID()].ptr
            handle = GUI.UUIDToWidgetMap[self.getUUID()].findHandle(objectName)
            return handle.getText().stdstr()

        @staticmethod
        def GetIP(self,objectName):
            ptr = GUI.UUIDToWidgetMap[self.getUUID()].ptr
            handle = GUI.UUIDToWidgetMap[self.getUUID()].findHandle(objectName)
            return handle.getIP().stdstr()

if __name__ == "__main__":
    Debug.enabledDirectPrintMode()
    GUI.Button("123","23")
    GUI.Button("345","236")
    GUI.Label("123","45")
    Debug.disabledDirectPrintMode()