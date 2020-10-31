from GUI import GUI,Widget,EventType
from GUIUtility import GUIUtility
from Debug import Debug

class SettingDialog(Widget):
    def __init__(self):
        super().__init__(tabMode = False,dialogMode = True)

    def OnGUI(self):
        GUI.BeginGUI(self)
        
        GUI.BeginTab('Tab_Main',True)
        GUI.BeginSubTab('Tab111','Tab1')

        GUI.BeginVerticalLayout()
        GUI.Label('label3','line 1')
        GUI.Label('label4','line 2')
        GUI.EndLayout()

        GUI.EndSubTab()

        GUI.BeginSubTab('Tab222','Tab2')

        GUI.BeginVerticalLayout()
        GUI.Label('label5','line 24')
        GUI.Label('label6','line 25')
        GUI.EndLayout()

        GUI.EndSubTab()

        GUI.EndTab()

        GUI.EndGUI()

    def OnStart(self):
        GUI.set.WindowTitle(self,'hahahah')
        GUI.set.WindowIcon(self,'C:\\Users\\Timor\\Desktop\\testIco.bmp')
        GUI.set.Width(self,"spinBox1",200)
        GUI.set.Width(self,"spinBox2",200)
        Debug.printInfo("finished")
        

    def OnClose(self):
        GUIUtility.MessageBox('2','3')

    @GUI.Slot(receiver = "button",eventType = EventType.Button_Click)
    def OnClick_Button(self):
        GUIUtility.MessageBox('1','2')