# coding=utf-8
from GUI import GUI,Widget,EventType
import socket
import threading
import sys
import os
import random
import time
from Debug import Debug
from GUIUtility import GUIUtility
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
        self.startTime = time.time()

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
        #del self.MessagesPool[0]
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
    def __init__(self):
        super().__init__()
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
        GUI.set.SetIP(self,"edit_serverIP","127.0.0.1")
        GUI.set.SetLineEditText(self,"edit_port","30001")
        #GUI.modify.AppendTableItem(self,"table_client",["12","23","45","6","6","6"])

    def OnClose(self):
        pass

    @GUI.Slot(receiver = "button_StartServer",eventType = EventType.Button_Click)
    def OnClick_button_StartServer(self):
        ip = GUI.get.GetIP(self,"edit_serverIP")
        port = GUI.get.GetLineEditText(self,"edit_port")
        self.serverPtr = Server_Impl(ip,(int)(port))
        if self.serverPtr.run():
            GUI.set.SetControlEnabled(self,"button_StartServer",False)
            GUI.set.SetControlEnabled(self,"edit_serverIP",False)
            GUI.set.SetControlEnabled(self,"edit_port",False)
            GUI.set.SetControlEnabled(self,"button_closeServer",True)
        def client_table_updater():
            while True:
                try:
                    rowCount = GUI.get.GetTableRowCount(self,"table_client")
                    index = 0
                    for key,value in self.serverPtr.clientMap.items():
                        info = value
                        if(index >= rowCount):
                            GUI.modify.AppendTableItem(self,"table_client",[info.IP,(str)(info.Port),str(info.getMessageCount()),str((time.time()-info.startTime))+"秒","已连接","None"])          
                        else:
                            GUI.modify.SetTableItem(self,"table_client",index,2,str(info.getMessageCount()))
                            GUI.modify.SetTableItem(self,"table_client",index,3,str((time.time()-info.startTime))+"秒")
                        index+=1
                except Exception as e:
                    Debug.printError(str(e))
                    break
                time.sleep(0.1)
        threading.Thread(target = client_table_updater).start()

    @GUI.Slot(receiver="table_client",eventType=EventType.TableView_Selection_Chanced)
    def On_table_client_selection_changed(self,index):
        self.index = index
        GUI.set.SetControlEnabled(self,"button_export",index!=-1)
        GUI.set.SetControlEnabled(self,"button_deleteClient",index!=-1)

    @GUI.Slot(receiver="button_export",eventType=EventType.Button_Click)
    def OnClick_button_export(self):
        path = GUIUtility.AskSaveFile("保存隐蔽信道文件","CSV file(*.csv)")
        info = list(self.serverPtr.clientMap.values())[self.index].MessagesPool

        def exportData(fileName:str,Infos:list)->bool:
            import csv
            try:
                with open(fileName, 'w', newline='') as f:
                    f_csv = csv.writer(f)
                    f_csv.writerow(["IPDs","Content"])
                    for i in range(0,len(Infos)):
                        if(isinstance(Infos[i],list)):
                            row = []
                            for j in range(0,len(Infos[i])):
                                row.append(Infos[i][j])
                            f_csv.writerow(row)
                        else:
                            f_csv.writerow([Infos[i]])
            except Exception as e:
                Debug.printError(str(e))
                return False
            return True

        if exportData(path,info):
            Debug.printInfo("导出成功!")
        else:
            Debug.printInfo("导出失败!")

    @GUI.Slot(receiver="button_closeServer",eventType=EventType.Button_Click)
    def OnClick_button_closeServer(self):
        self.serverPtr.shutDown()
        GUI.set.SetControlEnabled(self,"button_StartServer",True)
        GUI.set.SetControlEnabled(self,"button_closeServer",False)