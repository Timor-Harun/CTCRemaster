from GUI import GUI,Widget,EventType
from GUIUtility import GUIUtility
from CTCBase import *

import uuid
import threading
import time
import sys
import time
import random

class JitterBug_Impl(CTCBase):

    def __init__(self,IP,port,count):
        super().__init__(IP,port,count)
        self.mode = 0

    def run(self):
        if not self.valid:
            return

        for i in range(1, self.count):
            info = random.randint(0, 1)  # 随机生成隐蔽信息

            current_threshold = None

            #获取一个正常信道的IPD，进行额外延迟
            normal_IPD = Normal.Get()     
            new_IPD = JitterBug.getExtraDelay(info,normal_IPD,self.w)
            #等待的时间

            time.sleep(new_IPD/1000)
            self.s.send(str(i).encode('utf-8'))  # 发送一个数据包
            self.pushProcess()

        s.send('Fin'.encode('utf-8'))   # 结束标志
        # 关闭连接
        s.close()

    def setParameter(self,**kwargs):
        if("w" not in kwargs):
            return 
        self.w = (int)(kwargs["w"])
        self.valid = True

    @staticmethod
    def getExtraDelay(bit,IPD,w):
        if(bit == 1): #如果发送比特1，增加延迟使得IPD能被w整除
            temp = (int)(IPD/w)+1
            return temp * w
        elif(bit == 0):#如果发送比特0，增加延迟使得IPD能被w/2整除，同时不能被w整除
            wh = (int)(w/2) #w的二分之一
            temp = (int)(IPD/wh)+1
            ret = temp * wh
            while ret%w==0:
                ret = ret+wh
            return ret
        return -1

class JitterBug(Widget):
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
        GUI.EndLayout()
        GUI.EndGroup()

        GUI.BeginGroup("Propery Setting")
        GUI.BeginHorizontalLayout()
        GUI.Label("JitterBug阈值w:")
        GUI.LineEdit("edit_w")
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
        pass
    def OnClose(self):
        pass