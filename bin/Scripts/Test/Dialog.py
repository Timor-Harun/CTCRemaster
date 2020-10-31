from GUI import GUI,Widget,EventType
from GUIUtility import GUIUtility
from Debug import Debug

class your_dialog(Widget):
    def __init__(self):
        super().__init__(tabMode = False,dialogMode = True)

    def OnGUI(self):
        GUI.BeginGUI(self)
        # input some GUI command here
        GUI.EndGUI()

    def OnStart(self):
        pass

    def OnClose(self):
        pass