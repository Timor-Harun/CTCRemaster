from GUI import GUI,Widget,EventType
import win32gui,win32con
import win32api
import uuid
import threading
import time
from GUIUtility import GUIUtility
class testWidget(Widget):
    def __init__(self):
        pass

    def OnGUI(self):
        GUI.BeginGUI(self)
        GUI.BeginGroup("Group 1")
        GUI.BeginHorizontalLayout()
        GUI.Button("testBtn1","testBtn1")
        GUI.Button("testBtn2","testBtn2")
        GUI.LineEdit("testEdit")
        GUI.EndLayout()
        GUI.EndGroup()

        GUI.BeginGroup("Group 2")
        GUI.BeginVerticalLayout()
        GUI.Button("testBtn3","testBtn3")
        GUI.Button("testBtn4","testBtn4")
        GUI.CheckBox("testCheckBox","testCheckBox",True)
        GUI.ProgressBar("testProgressBar")
        GUI.EndLayout()
        GUI.EndGroup()

        GUI.EndGUI()

    @GUI.Slot(receiver = "testBtn1",eventType = EventType.Button_Click)
    def OnClick_Button_Test1(self):
        win32api.MessageBox(0, "test1", "test1",win32con.MB_OK)

    @GUI.Slot(receiver = "testBtn2",eventType = EventType.Button_Click)
    def OnClick_Button_Test2(self):
        GUI.set.SetLineEditText(self,"testEdit","heiheihei!")

    @GUI.Slot(receiver = "testBtn3",eventType = EventType.Button_Click)
    def OnClick_Button_Test3(self):
        GUI.set.SetLineEditText(self,"testEdit",GUIUtility.AskOpenFile("open file?"))
        #GUI.SetStyleSheet("testBtn2","QPushButton{background-color:#FFF8DC;border: 3px solid #FFF8DC;font-family: \"微软雅黑\";font-weight:bold;font-size:14px;}")

    @GUI.Slot(receiver = "testBtn4",eventType = EventType.Button_Click)
    def OnClick_Button_Test4(self):
        import threading
        def internal_Function():
            for i in range(0,101):
                time.sleep(0.1)
                GUI.set.SetProgressBarValue(self,"testProgressBar",i)
        threading.Thread(target = internal_Function).start()


    @GUI.Slot(receiver = "testEdit",eventType = EventType.Edit_Finished)
    def OnEdit_Finished(self):
        GUIUtility.MessageBox("editing finished","text = {}".format(GUI.GetLineEditText("testEdit")))

    @GUI.Slot(receiver = "testCheckBox",eventType = EventType.CheckState_Changed)
    def OnCheckState_Changed(self):
        GUI.set.SetLineEditText(self,"testEdit","testCheckBox changed!")

    def OnClose(self):
        pass