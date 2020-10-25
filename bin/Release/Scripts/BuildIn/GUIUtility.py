from Debug import Debug
import qt_module_wrapped
class GUIUtility(object):
    @staticmethod
    def AskOpenFile(title,filter = str(),default = str()):
        return qt_module_wrapped.qutility_class.openFile(qt_module_wrapped.qstr(title), \
                                                         qt_module_wrapped.qstr(filter),\
                                                         qt_module_wrapped.qstr(default))

    @staticmethod
    def AskSaveFile(title,filter = str(),default = str()):
        return qt_module_wrapped.qutility_class.saveFile(qt_module_wrapped.qstr(title),\
                                                         qt_module_wrapped.qstr(filter),\
                                                         qt_module_wrapped.qstr(default))
    @staticmethod
    def MessageBox(title:str,message:str):
        qt_module_wrapped.qutility_class.messageBox(qt_module_wrapped.qstr(title),qt_module_wrapped.qstr(message))

if __name__ == "__main__":
    import os
    import sys
    sys.path.append(os.path.abspath(os.path.join(__file__, "../../..")))
    import qt_module_wrapped
    Debug.enabledDirectPrintMode()
    Debug.printError("123")
    Debug.disabledDirectPrintMode()