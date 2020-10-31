from Debug import Debug
import sys
import os.path

class Config():

    __namespace_data_dict = {}
    __currentNameSpace = "std"
    __defalutSavePath = sys.path[0]+"\\Config\\data.json"

    @staticmethod
    def __initilize():
        pass

    @staticmethod
    def __finalize():
        pass

    @staticmethod
    def insertKey(key:str,value):
        pass

    @staticmethod
    def containsKey(key:str):
        pass

    @staticmethod
    def getKey(key:str):
        pass

    @staticmethod
    def __readFile():
        pass

    @staticmethod
    def __writefile():
        pass

    @staticmethod
    def __setPath(path):
        pass

    @staticmethod
    def __getPath():
        pass