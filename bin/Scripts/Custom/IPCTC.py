from GUI import GUI,Widget,EventType
import win32gui,win32con
import win32api
import uuid
import threading
import time
from GUIUtility import GUIUtility
import sys
from CTCBase import *
import time
import random

class IPCTC_Impl(CTCBase):

    MODE_SINGLE = 1 #单一间隔
    MODE_TURN =2    #多个间隔轮换

    def __init__(self,IP,port):
        Debug.printInfo("IPCTC() called")
        super().__init__(IP,port)
        self.mode = 0

    #与C++ 对接，设置信道参数
    #合法的设置方式 IPCTC.setParameter(threshold = [40,60,80],period=50) 或 IPCTC.setParameter(threshold = [50])
    #涉及对threshold的类型判断
    def setParameter(self,**kwargs)->bool:
        self.kwargs = kwargs
        if("thresholds" not in self.kwargs):
            raise ValueError("missing param 'thresholds'")
            return False
        self.thresholds = self.kwargs["thresholds"]

        if(str(type(self.thresholds)) == "<class 'list'>"):
            if(len(self.thresholds)>1):
                if("period" not in self.kwargs):
                    raise ValueError("missing param 'period'")
                else:
                    self.mode = self.MODE_TURN
                    self.period = (int)(self.kwargs["period"])
                    self.threshold_Index = 0
                    return True
            else:
                self.mode = self.MODE_SINGLE
                self.thresholds = self.thresholds[0]
        else:
            raise ValueError("invalid param 'threshold'")
            return False
        return True

    #运行函数
    #对于IPCTC，已经根据threshold的元素的数量，判断是多个间隔轮换，还是只有单个间隔
    def run(self)->None:
        self.clearProcess()
        def run_Internal():
            try:
                self.s.send(("IPCTC package,content="+str(0) + " Count = "+str(self.count)).encode('utf-8')) # 发送一个数据包
                Debug.printInfo("已发送 0")
                for i in range(1, self.count):
                    info = random.randint(0, 1)  # 随机生成隐蔽信息
                    current_threshold = None
                    #轮换模式
                    if self.mode == self.MODE_TURN:
                        #周期轮换
                        if(i % self.period == 0):
                            self.threshold_Index = (self.threshold_Index +1)%(len(self.thresholds))
                        current_threshold = self.thresholds[self.threshold_Index]
                    #单一模式
                    else:
                        current_threshold = self.thresholds

                    if info == 1:  
                        # 发送比特1，在threshold/2 毫秒发送一个数据包
                        time.sleep(current_threshold/2000)
                        self.s.send(("IPCTC package,content="+str(i)).encode('utf-8'))  # 发送一个数据包
                        Debug.printInfo("已发送 1")
                        #发送完以后，再等待threshold/2 毫秒，到达下一个间隔周期
                        time.sleep(current_threshold/2000)
                        #Debug.printInfo("已发送",i)
                    else:
                        # 发送0，静默t ms    
                        time.sleep(current_threshold / 1000)
                        #Debug.printInfo("第",i,"个数据包静默")
                        Debug.printInfo("已发送 0")
                    self.pushProcess()

                self.s.send('Fin'.encode('utf-8'))   # 结束标志
                # 关闭连接
                self.s.close()
            except Exception as e:
                Debug.printError(str(e))
        threading.Thread(target=run_Internal).start()


    def getParameterRequirement(self)->list:
        #format ： [param's name,param'stype,isNotNull,default value]
        return [["thresholds","list",True,"[40,60,80]"],["period","int",False,0]]

class IPCTC(Widget):
    def __init__(self):
        pass

    def OnGUI(self):
        GUI.BeginGUI(self)
        GUI.BeginGroup("Server Information")
        GUI.BeginHorizontalLayout()
        GUI.Label("服务器IP地址")
        GUI.IPAddress("edit_serverIP")
        GUI.Spacer(50)
        GUI.Label("服务器端口号")
        GUI.LineEdit("edit_port")
        GUI.Label("发包数量")
        GUI.LineEdit("edit_count")
        GUI.EndLayout()
        GUI.EndGroup()

        GUI.BeginGroup("Propery Setting")
        GUI.BeginHorizontalLayout()
        GUI.Label("间隔时间")
        GUI.LineEdit("edit_interval")
        GUI.Spacer(50)
        GUI.Label("轮换模式")
        GUI.CheckBox("check_turn","")
        GUI.Label("轮换周期")
        GUI.LineEdit("edit_period")
        GUI.EndLayout()
        GUI.EndGroup()

        GUI.BeginGroup("Display")
        GUI.BeginHorizontalLayout()
        GUI.Label("发送进度")
        GUI.ProgressBar("progressBar_send")
        GUI.EndLayout()
        GUI.EndGroup()

        GUI.BeginHorizontalLayout()
        GUI.Spacer(400)
        GUI.Button("button_Connect","连接服务器")
        GUI.Button("button_Send","开始发送")
        GUI.EndLayout()

        GUI.EndGroup()

        GUI.EndGUI()
    
    def OnStart(self):
        GUI.set.SetControlEnabled(self,"button_Connect",True)
        GUI.set.SetControlEnabled(self,"button_Send",False)
        GUI.set.SetControlEnabled(self,"edit_period",False)
        GUI.set.SetIP(self,"edit_serverIP","127.0.0.1")
        GUI.set.SetLineEditText(self,"edit_port","30001")
    @GUI.Slot(receiver = "button_Connect",eventType = EventType.Button_Click)
    def OnClick_button_Connect(self):
        ip = GUI.get.GetIP(self,"edit_serverIP")
        port = GUI.get.GetLineEditText(self,"edit_port")

        self.ipctc = IPCTC_Impl(ip,int(port))
        if(self.ipctc.testConnect()):
            GUI.set.SetControlEnabled(self,"button_Connect",False)
            GUI.set.SetControlEnabled(self,"button_Send",True)

    @GUI.Slot(receiver = "button_Send",eventType = EventType.Button_Click)
    def OnClick_button_Send(self):
        self.ipctc.run()
        
    @GUI.Slot(receiver = "check_turn",eventType = EventType.CheckState_Changed)
    def OnCheckStateChanged_check_turn(self):
        checked = GUI.get.GetChecked(self,"check_turn")
        GUI.set.SetControlEnabled(self,"edit_period",checked)

    @GUI.Slot(receiver = "button_Send",eventType = EventType.Button_Click)
    def OnClick_button_Send(self):
        import json
        checked = GUI.get.GetChecked(self,"check_turn")
        try:
            param_interval = json.loads(GUI.get.GetLineEditText(self,"edit_interval"))
            typeStr = str(type(param_interval))
            Debug.printInfo("param_interval={} typeStr={}".format(param_interval,typeStr))
            if checked:
                if typeStr != "<class 'list'>":
                    Debug.printError("IPCTC参数'间隔时间' 类型错误: 需要类型:list,实际类型:"+typeStr)
                    return
                else:
                    param_period = json.loads(GUI.get.GetLineEditText(self,"edit_period"))
                    self.ipctc.setParameter(thresholds = param_interval,period = param_period)
            else:
                if typeStr != "<class 'int'>" or typeStr != "<class 'float'>":
                    Debug.printError("IPCTC参数'间隔时间' 类型错误: 需要类型:int 或 float,实际类型:"+typeStr)
                    return
                else:
                    self.ipctc.setParameter(thresholds = param_interval)
            self.ipctc.count = json.loads(GUI.get.GetLineEditText(self,"edit_count"))
        except Exception as e:
            Debug.printError(str(e))
            return

        self.ipctc.run()

    def OnClose(self):
        pass