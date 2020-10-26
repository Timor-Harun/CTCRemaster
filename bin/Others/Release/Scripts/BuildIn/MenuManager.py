import win32gui,win32con
import win32api
from Debug import Debug
from GUIUtility import GUIUtility
MenuItemMap = dict()
"""
类名：MenuManager
功能：负责管理菜单栏的条目
"""
class MenuManager():

    """
    方法：__SplitPath
    功能：根据输入的路径，根据'/'将路径分割成list
    参数：path - 目标菜单条目的路径 
    返回：无
    """
    @staticmethod
    def __SplitPath(path:str)->list:
         return path.replace('\\','/').split('/')

    """
    方法：InsertMenuItem
    功能：插入一条菜单
    参数：path - 目标菜单条目的路径 
    参数：func - 目标菜单条目触发的槽函数指针
    返回：uuid(str),代表目标菜单栏目的uuid值  
    """
    @staticmethod
    def InsertMenuItem(path,func,checkable,group,pos,shortcut):
        try:
            global MenuItemMap
            import uuid
            ret = str(uuid.uuid1())[0:8]
            shortCutInfo = MenuManager.__PraseShortCut(shortcut)
            MenuItemMap[ret] = [MenuManager.__SplitPath(path),checkable,group,pos,shortCutInfo,func]
            return str(ret)
        except Exception as e:
            Debug.printError(e)
            return ""
    
    """
    方法：ClearMenuItem
    功能：清除所有菜单
    参数：无
    返回：无
    """
    @staticmethod
    def ClearMenuItem():
        global MenuItemMap
        MenuItemMap.clear()

    @staticmethod
    def GetMenuItemInfo():
        global MenuItemMap
        infos = []
        for key in MenuItemMap.keys():
            info = []
            info.append(key)
            info = info + MenuItemMap[key][0:5]
            infos.append(info)
        return infos
        
    """
    方法：GetMenuItemFunction
    功能：获取槽函数指针
    参数：无
    返回：无
    """
    @staticmethod
    def GetFunction(uuid):
        global MenuItemMap
        return MenuItemMap[uuid][-1]

    @staticmethod
    def __PraseShortCut(shortCut):
        def is_english_char(ch):
            if ord(ch) not in range(97,122) and ord(ch) not in range(65,90):
                return False
            else:
                return True
        splitted = shortCut.split('+')
        modifierCtrl = False
        modifierShift = False
        keyCode = None
        for s in splitted:
            if s.upper() == "CTRL":
                if not modifierCtrl:
                    modifierCtrl = True
                else:
                    Debug.printWarning("Reuse of 'CTRL' modifier")
            elif s.upper() == "SHIFT":
                if not modifierShift:
                    modifierShift = True
                else:
                    Debug.printWarning("Reuse of 'SHIFT' modifier")
            else:
                 if len(s) == 1 and is_english_char(s[0]):
                    if not keyCode:
                        keyCode = s.upper()[0]
                    else:
                        Debug.printWarning("Cannot use two key for shortCut")
                 else:
                    Debug.printWarning("Unidentified str:"+s)
                    return []
        return [modifierCtrl,modifierShift,keyCode]

                        


