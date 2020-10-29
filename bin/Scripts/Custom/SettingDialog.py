from GUI import GUI,Widget,EventType
from GUIUtility import GUIUtility

class SettingDialog(Widget):
    def __init__(self):
        super().__init__(tabMode = False,dialogMode = True)

    def OnGUI(self):
        GUI.BeginGUI(self)
        GUI.BeginHorizontalLayout()
        GUI.Button("button","按钮")
        GUI.EndLayout()
        GUI.EndGUI()

    def OnStart(self):
        GUI.set.WindowTitle(self,'hahahah')
        GUI.set.WindowIcon(self,'C:\\Users\\Timor\\Desktop\\testIco.bmp')


    def OnClose(self):
        GUIUtility.MessageBox('2','3')

    @GUI.Slot(receiver = "button",eventType = EventType.Button_Click)
    def OnClick_Button(self):
        GUIUtility.MessageBox('1','2')