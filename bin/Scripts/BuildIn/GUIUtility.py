from Debug import Debug,qt_module_wrapped

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

