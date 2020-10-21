import pysnooper

@pysnooper.snoop()
def a():
    b = 1
    c = b*b

a()