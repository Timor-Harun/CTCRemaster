#Debug 系统的实现
#通过消息池，与C++进行通信

########## Build-In ###########
import traceback
import inspect
import sys
import ctypes
import os

if __name__ == "__main__":
    base_path = os.path.abspath(os.path.join(sys.path[0],"../.."))
else:
    base_path = os.getcwd()
try:
    ctypes.windll.LoadLibrary(base_path+'\\boost_python39-vc142-mt-gd-x64-1_74.dll')
except Exception as e:
    ctypes.windll.LoadLibrary(base_path+'\\bin\\boost_python39-vc142-mt-gd-x64-1_74.dll')
    base_path = base_path+"\\bin"
ctypes.windll.LoadLibrary(base_path+'\\Qt5Chartsd.dll')
ctypes.windll.LoadLibrary(base_path+'\\Qt5Guid.dll')
ctypes.windll.LoadLibrary(base_path+'\\Qt5Svgd.dll')
ctypes.windll.LoadLibrary(base_path+'\\Qt5Widgetsd.dll')


########## Qt Wrapped ###########
import qt_module_wrapped
consolemsg_class = qt_module_wrapped.consolemsg_class
consolemsgpool_class = qt_module_wrapped.consolemsgpool_class
qstr = qt_module_wrapped.qstr
msgtype_enum = qt_module_wrapped.msgtype_enum
#### Class Debug ####
# 提供将 信息 输出到控制台的接口
# 所有消息并不能直接输出，而是写入 与C++ 共享的consolemsgpool_class（消息池）的一个对象的之中，作为缓冲区
# C++ 部分从 缓冲区中不断地取出信息，从而实现消息的输出

class Debug(object):
    # 消息池的指针
    __poolPtr = None

    # 获取调用的信息，其中包括函数的名称，参数，以及所在文件的行数
    @staticmethod
    def getCalledInfo():
        frameInfo=inspect.stack()[2]
        args, _, _,_ = inspect.getargvalues(frameInfo.frame)
        return ("File:"+frameInfo.filename.split("\\")[-1].split("/")[-1]+" "+frameInfo.function+str(args).replace('\'','').replace('[','(').replace(']',')').replace(' ','')+" at Line:"+str(frameInfo.lineno))

    # C++ 调用类，注入 消息池的指针
    @staticmethod
    def injectPoolPtr(ptr:consolemsgpool_class):
        if(Debug.__poolPtr):
            raise Exception("无法手动调用injectPoolPtr方法")
        else:
            Debug.__poolPtr = ptr

    # 输出普通信息
    @staticmethod
    def printInfo(message)->None:
        calledInfo = Debug.getCalledInfo()
        Debug.__poolPtr.pushMessage(consolemsg_class(qstr(calledInfo),qstr(message),msgtype_enum.Info))

    # 输出警告信息
    @staticmethod
    def printWarning(message)->None:
        calledInfo = Debug.getCalledInfo()
        Debug.__poolPtr.pushMessage(consolemsg_class(qstr(calledInfo),qstr(message),msgtype_enum.Warning))

    # 输出错误消息
    @staticmethod
    def printError(message)->None:
        calledInfo = Debug.getCalledInfo()
        Debug.__poolPtr.pushMessage(consolemsg_class(qstr(calledInfo),qstr(message),msgtype_enum.Error))

