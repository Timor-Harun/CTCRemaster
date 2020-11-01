from GUI import GUI,Widget,EventType
from GUIUtility import GUIUtility
import qt_module_wrapped
from Debug import Debug

class SettingDialog(Widget):
    def __init__(self):
        super().__init__(tabMode = False,dialogMode = True)
        self.fontInfo = None

    def OnGUI(self):
        GUI.BeginGUI(self)
        
        GUI.BeginTab('Tab_Main',True)
        GUI.BeginSubTab('Tab_Display','展示')
        GUI.BeginGroup("字体")
        GUI.BeginVerticalLayout()
        GUI.BeginHorizontalLayout()
        GUI.Label('label_fontInfo1','当前字体信息')
        GUI.Label('label_fontInfo2','')
        GUI.Button('button_fontSetting','字体设置')
        GUI.EndLayout()
        GUI.EndLayout()
        GUI.EndGroup()
        GUI.EndSubTab()

        GUI.BeginSubTab('','Tab2')

        GUI.BeginVerticalLayout()
        GUI.Label('label5','line 24')
        GUI.Label('label6','line 25')
        GUI.EndLayout()

        GUI.EndSubTab()

        GUI.EndTab()

        GUI.EndGUI()

    def OnStart(self):
        GUI.set.WindowTitle(self,"设置")
        GUI.set.WindowProperty(self,"maximunWidth",600)
        GUI.set.WindowProperty(self,"maximunHeight",400)
        GUI.set.WindowProperty(self,"minimumWidth",600)
        GUI.set.WindowProperty(self,"minimumHeight",400)

        qfontInfo = GUI.get.FontInfo(self,"label_fontInfo1")

        family = qfontInfo.family().stdstr()
        bold = str(qfontInfo.bold())
        italic = str(qfontInfo.italic())
        psize = str(qfontInfo.pointSize())

        fontInfoStr = "family = "+family + " bold = "+bold+" italic = "+italic+" psize = "+psize
        GUI.set.Property(self,"label_fontInfo2","text",fontInfoStr)


        
    def OnClose(self):
        GUIUtility.MessageBox('2','3')

    @GUI.Slot(receiver = "button_fontSetting",eventType = EventType.Button_Click)
    def OnClick_Button(self):
        qfont = (GUIUtility.AskFont("ask"))
        Debug.printInfo("famliyName="+qfont.getFamilyName().stdstr())