# coding=utf-8
from GUI import GUI,Widget,EventType
import socket
import threading
import sys
import os
import random
import time
from Debug import Debug

class ClientInfo(object):

    CLIENT_STATUS_CONNECTED = 0
    CLIENT_STATUS_DISCONNECTED = 1
    CLIENT_STATUS_FOCUSQUIT = 2
    CLIENT_STATUS_LOSTCONNECTION = 3
    CLIENT_STATUS_INNERERROR = 4

    def __init__(self,IP,Port):
        self.IP = IP
        self.Port = Port
        self.MessagesPool = []
        self.Status = -1
        self.lastTime = 0

    def clear(self):
        self.MessageCount = []
        self.LastMessage = str()
        self.Status = -1

    def getMessageCount(self):
        return len(self.MessagesPool)

    def addMessage(self,msg):
        currentTime = time.time()
        self.MessagesPool.append([currentTime - self.lastTime,msg])
        self.lastTime = currentTime

    def getFrontMessage(self):
        msg = self.MessagesPool[0]
        del self.MessagesPool[0]
        return msg

    def setStatus(self,status):
        self.Status = status

    def getStatus(self):
        return self.Status

    def getSocketName(self):
        return [self.IP,self.Port]

class Server_Impl(object):
    
    def __init__(self,IP,port):
        # socket列表
        self.socket_list = []
        self.IP = IP
        self.port = port
        self.clientMap = {}
        Debug.printInfo("Test Info")
        Debug.printWarning("Test Warning")
        Debug.printError("Test Error")

    def run(self)->bool:
        try:
            # 创建socket对象
            self.s = socket.socket()
            # 绑定本地IP和端口
            Debug.printInfo("IP="+self.IP+" Port="+str(self.port))
            self.s.bind((self.IP, self.port))
            # 开始监听
            self.s.listen()
            # 循环等待连接
            Debug.printInfo("waiting for client to join in...")
            t =  threading.Thread(target=self.waitForClient)
            t.start()
            #t.join()
        except Exception as e:
            Debug.printError(str(e))
            return False
        return True

    def getClientMap(self)->map:
        return self.clientMap

    def waitForClient(self)->None:
        while True:
            client, addr = self.s.accept()
            if(addr in self.clientMap):
                info = (ClientInfo)(self.clientMap[addr])
                info.clear()
            else:
                socket_info_list = (list)(addr)
                info = ClientInfo((str)(socket_info_list[0]),(int)(socket_info_list[1]))
                info.setStatus(ClientInfo.CLIENT_STATUS_CONNECTED)
                self.clientMap[addr] = info

            Debug.printInfo("connected Client:"+str(client))
            # 将客户端加入列表
            self.socket_list.append(client)
            
            # 为该客户端开辟一个线程
            threading.Thread(target=self.server_target, args=(client,addr,)).start()

    def rec_from_client(self,client,addr)->str:
        try:
            ret =  client.recv(2048).decode('utf-8')
            return ret
        except Exception as e:
            self.socket_list.remove(client)
            self.clientMap[client.getsockname()].setStatus(ClientInfo.CLIENT_STATUS_INNERERROR)
            return None


    def server_target(self,client,addr):
        try:
            while True:
                content = self.rec_from_client(client,addr)
                Debug.printInfo("received from "+str(addr)+", content="+str(content))
                if str(content) == 'Fin' or content == None:
                     Debug.printInfo("Finished")
                     self.socket_list.remove(client)
                     client.shutdown(2)
                     client.close()
                     self.clientMap[addr].setStatus(ClientInfo.CLIENT_STATUS_DISCONNECTED)
                     break
                else:
                     self.clientMap[addr].addMessage(content)
        except Exception as e:
            self.socket_list.remove(client)
            self.clientMap[addr].setStatus(ClientInfo.CLIENT_STATUS_INNERERROR)
            Debug.printError(str(e))

    def shutDown(self):
        try:
            for clientSocket in self.socket_list:
                clientSocket.shutdown(2)
                clientSocket.close()
            if self.socket_list:
                self.socket_list.clear()
                self.clientMap.clear()
                self.s.shutdown(2)
            self.s.close()
            Debug.printInfo("Server Closed")
        except Exception as e:
            Debug.printError(str(e))    

class Server(Widget):
    def OnGUI(self):
        GUI.BeginGUI(self)
        GUI.BeginGroup("Server Infomation")
        GUI.BeginHorizontalLayout()
        GUI.Label("服务器IP地址")
        GUI.IPAddress("edit_serverIP")
        GUI.Label("服务器端口号")
        GUI.LineEdit("edit_port")
        GUI.Button("button_StartServer","开启服务器")
        GUI.EndLayout()
        GUI.EndGroup()

        GUI.BeginGroup("Client Information")
        GUI.BeginHorizontalLayout()
        GUI.Table("table_client",["IP地址","端口号","消息总数","连接时间","连接状态","最后消息"])
        GUI.BeginVerticalLayout()
        GUI.Button("button_export","导出数据")
        GUI.Button("button_deleteClient","删除Client")
        GUI.Button("button_closeServer","关闭服务器")
        GUI.EndLayout()
        GUI.EndLayout()
        GUI.EndGroup()
        GUI.EndGUI()

    def OnStart(self):
        GUI.set.SetControlEnabled(self,"button_export",False)
        GUI.set.SetControlEnabled(self,"button_deleteClient",False)
        GUI.set.SetControlEnabled(self,"button_closeServer",False)
        #GUI.modify.AppendTableItem(self,"table_client",["12","23","45","6","6","6"])

    def OnClose(self):
        pass
