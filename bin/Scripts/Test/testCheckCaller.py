import traceback
import functools
import sys

def Nullfunction():
    pass
def CheckCaller(caller:str):
    def decorator(func):
        @functools.wraps(func)
        def wrapper(*args, **kwargs):
            f = sys._getframe()
            caller_name=f.f_back.f_code
            if(caller!=caller_name.co_name):
                print("caller error:"+caller_name.co_name +" required:"+caller)
                return lambda X: 0
            else:
                return func(*args, **kwargs)
        return wrapper
    return decorator
    
@CheckCaller(caller = "b")
def a():
    print("a")

def b():
    a()

b()



        