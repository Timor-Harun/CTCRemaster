from abc import ABC,abstractmethod
import socket
import threading

from Debug import Debug

class CTCBase(ABC):
    def __init__(self,IP,port):
        self.IP = IP    
        self.port =port  
        self.process = 0 
        self.count = 0
        self.kwargs = {}

    def getProcessPercent(self)->float:
        return 100.0 * (self.process+1) / (float)(self.count)

    def clearProcess(self)->None:
        self.process = 0

    def pushProcess(self)->None:
        self.process+=1

    def testConnect(self)->bool:
        try:
            self.s = socket.socket()
            self.s.connect((self.IP, self.port))
            Debug.printInfo("connect to Server ip={} port ={}".format(self.IP,self.port))
            return True
        except Exception as e:
            Debug.printInfo(str(e))
            return False

    def setCount(self,count)->None:
        self.count = count

    def shutDown(self)->bool:
        try:
            self.s.shutdown(2)
            self.s.close()
            Debug.printInfo("Disconnect from Server(ip="+self.IP+" ,Port="+str(self.port)+")")
            return True
        except Exception as e:
            Debug.printInfo(str(e))
            return False

    @abstractmethod
    def run(self):
        pass

    @abstractmethod
    def setParameter(self,kwargs):
        pass

    @abstractmethod
    def getParameterRequirement(self):
        pass
