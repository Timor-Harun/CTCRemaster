import functools
import win32gui,win32con
import win32api
from MenuManager import MenuManager

class Menu():
    @staticmethod
    def MenuItem(path,checkable,group = -1,pos = -1,shortcut = str()):
        if len(path) == 0  or path[0] =='/' or path[-1] =='/':
            Debug.printWarning("Invalid path")
        def decorator(func):
            MenuManager.InsertMenuItem(path,func,checkable,group,pos,shortcut)
            @functools.wraps(func)
            def wrapper(*args, **kwargs):
                return func(*args, **kwargs)
            return wrapper
        return decorator
        

    