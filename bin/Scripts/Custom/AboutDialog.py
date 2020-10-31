from GUI import GUI,Widget,EventType,AlignmentFlag
from GUIUtility import GUIUtility
from Debug import Debug,qt_module_wrapped

class AboutDialog(Widget):
    def __init__(self):
        super().__init__(tabMode = False,dialogMode = True)

    def OnGUI(self):
        GUI.BeginGUI(self)
        # input some GUI command here
        GUI.BeginHorizontalLayout()
        GUI.Label(objectName="label",imageMode = True,imagePath = "C:\\Users\\Timor\\Desktop\\AboutIcon.jfif")
        GUI.BeginVerticalLayout()
        GUI.Spacer(50)
        GUI.Label("Label_Top","隐蔽信道检测实验平台 Ver 0.0002")
        GUI.Label("Label_Mid","Based On Qt Framework && Python && Boost Library")
        GUI.Label("Label_Bottom","Programmers：Timor && Harun")
        GUI.Label("Label_Bottom1","Support: Quan Sun")
        GUI.BeginHorizontalLayout()
        GUI.Label("Label_Bottom2","官网地址")
        GUI.Label("Label_Bottom3","https://coupon580.com/home")
        GUI.EndLayout()
        GUI.Spacer(50)
        GUI.EndLayout()
        GUI.EndLayout()

        GUI.EndGUI()

    def OnStart(self):
        GUI.set.Size(self,"label",200,200)
        GUI.set.WindowProperty(self,"minimumWidth",750)
        GUI.set.WindowProperty(self,"minimumHeight",300)
        GUI.set.WindowProperty(self,"maximumWidth",750)
        GUI.set.WindowProperty(self,"maximumHeight",300)
        GUI.set.WindowProperty(self,"windowTitle","关于 隐蔽信道检测平台")
        GUI.set.WindowProperty(self,"styleSheet",'QLabel#Label_Top,#Label_Mid{font-family: "楷体";font-size:20px}\
                                                  QLabel#Label_Bottom,#Label_Bottom1{font-family: "Arial";font-size:16px}')

        font = GUIUtility.AskFont("选择字体")
        GUI.set.LabelAlignment(self,"Label_Top",AlignmentFlag.AlignCenter)
        GUI.set.LabelAlignment(self,"Label_Mid",AlignmentFlag.AlignCenter)
        GUI.set.LabelAlignment(self,"Label_Bottom",AlignmentFlag.AlignCenter)
        GUI.set.LabelAlignment(self,"Label_Bottom1",AlignmentFlag.AlignCenter)

        #Debug.printInfo(str(font))
        GUI.set.Font(self,"Label_Bottom",font)
        GUI.set.Font(self,"Label_Bottom1",font)
        GUI.set.LabelHyperLinkMode(self,"Label_Bottom3",True)

    def OnClose(self):
        pass