import os
class Project:
    APP_PATH = "#build/$BuildMode/bin"
    LIB_PATH = "#build/$BuildMode/lib"

    @staticmethod
    def appPath(name) :
        return os.path.join(APP_PATH, name)

    @staticmethod
    def libPath(name) :
        return os.path.join(LIB_PATH, name)