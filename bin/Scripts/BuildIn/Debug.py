#Debug 系统的实现
#通过消息池，与C++进行通信
import traceback
import inspect
import sys
from qt_module_wrapped import consolemsg_class,consolemsgpool_class,qstr,msgtype_enum

class Debug(object):
    poolPtr = None

    @staticmethod
    def enabledDirectPrintMode():
        import threading
        import time
        def printFunction():
            Debug.isRunning = True
            while True:
                if not Debug.empty():
                    print(Debug.nextMessage())
                else:
                    if Debug.isRunning == False:
                        print("Debug ShutDown")
                        return
                    else:
                        time.sleep(0.0001)
        Debug.thread = threading.Thread(target = printFunction)
        Debug.thread.start()

    @staticmethod
    def getCalledInfo():
        frameInfo=inspect.stack()[2]
        args, _, _,_ = inspect.getargvalues(frameInfo.frame)
        return ("File:"+frameInfo.filename.split("\\")[-1].split("/")[-1]+" "+frameInfo.function+str(args).replace('\'','').replace('[','(').replace(']',')').replace(' ','')+" at Line:"+str(frameInfo.lineno))

    @staticmethod
    def injectPoolPtr(ptr):
        Debug.poolPtr = ptr

    @staticmethod
    def printInfo(message)->None:
        calledInfo = Debug.getCalledInfo()
        Debug.poolPtr.pushMessage(consolemsg_class(qstr(calledInfo),qstr(message),msgtype_enum.Info))

    @staticmethod
    def printWarning(message)->None:
        calledInfo = Debug.getCalledInfo()
        Debug.poolPtr.pushMessage(consolemsg_class(qstr(calledInfo),qstr(message),msgtype_enum.Warining))

    @staticmethod
    def printError(message)->None:
        calledInfo = Debug.getCalledInfo()
        Debug.poolPtr.pushMessage(consolemsg_class(qstr(calledInfo),qstr(message),msgtype_enum.Error))

    @staticmethod
    def disabledDirectPrintMode()->None:
        Debug.isRunning = False