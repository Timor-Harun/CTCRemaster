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

        GUI.BeginGroup("Group SpinBox Demo")
        GUI.BeginVerticalLayout()
        GUI.BeginHorizontalLayout()
        GUI.Label('随便编辑1')
        GUI.DoubleSpinBox('spinBox1',min = -12.0,max = 20,step = 0.1)
        GUI.EndLayout()
        GUI.BeginHorizontalLayout()
        GUI.Label('随便编辑2')
        GUI.DoubleSpinBox('spinBox2',min = -10.0,max = 20,step = 0.5)
        GUI.EndLayout()
        GUI.EndLayout()
        GUI.EndGroup()

        GUI.BeginGroup("Group Tab Demo")
        GUI.BeginTab('Tab_Main')

        GUI.BeginSubTab('Tab111','Tab1')

        GUI.BeginVerticalLayout()
        GUI.Label('line 1')
        GUI.Label('line 2')
        GUI.EndLayout()

        GUI.EndSubTab()

        GUI.BeginSubTab('Tab222','Tab2')

        GUI.BeginVerticalLayout()
        GUI.Label('line 24')
        GUI.Label('line 25')
        GUI.EndLayout()

        GUI.EndSubTab()

        GUI.EndTab()
        GUI.EndGroup()

        GUI.EndGUI()

    def OnStart(self):
        GUI.set.WindowTitle(self,'hahahah')
        GUI.set.WindowIcon(self,'C:\\Users\\Timor\\Desktop\\testIco.bmp')
        GUI.set.Width(self,"spinBox1",200)
        GUI.set.Width(self,"spinBox2",200)
        GUI.set.Property(self,"spinBox2","maximized",True)
        

    def OnClose(self):
        GUIUtility.MessageBox('2','3')

    @GUI.Slot(receiver = "button",eventType = EventType.Button_Click)
    def OnClick_Button(self):
        GUIUtility.MessageBox('1','2')