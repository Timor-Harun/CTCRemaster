from qt_module_wrapped import plotmanager_class,qcolor_class,double_vector,str_vector,int_vector
from Debug import Debug

class plt(object):
    __plotManager_ptr = None

    @staticmethod
    def SetPlotManagerPtr(ptr):
        if(not plt.__plotManager_ptr):
            plt.__plotManager_ptr = ptr

    @staticmethod
    def figure(index:int):
        plt.__plotManager_ptr.figure(index)

    @staticmethod
    def plot(x,y,title="plot",seriesName = "series",rgb = [0,0,0],xlabel = "X",ylabel = "Y",lineWidth = 1,windowTitle = "plot window"):
        if(not len(x) == len(y)):
            Debug.printError("数组x,y长度必须相等:x 长度为{} y 长度为{}".format(len(x),len(y)))
            return

        double_vector_x = double_vector()
        double_vector_y = double_vector()

        for i in range(len(x)):
            double_vector_x.append(x[i])
            double_vector_y.append(y[i])

        plt.__plotManager_ptr.plot(double_vector_x,double_vector_y,title,seriesName,qcolor_class(rgb[0],rgb[1],rgb[2]),xlabel,ylabel,lineWidth,windowTitle)

    @staticmethod
    def subplot(m:int,n:int,p:int):
        plt.__plotManager_ptr.subplot1(m,n,p)

    @staticmethod
    def bar(vars,varNames,label="bar",title="barView"):
        int_vector_var = int_vector()
        str_vct = str_vector()

        for var in vars:
            int_vector_var.append(var)
        for name in varNames:
            str_vct.append(name)
        plt.__plotManager_ptr.bar(int_vector_var,str_vct,label,title)

    @staticmethod
    def displayAll():
        plt.__plotManager_ptr.displayAll()