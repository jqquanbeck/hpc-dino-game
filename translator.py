from ctypes import *

cdll.LoadLibrary("./dinolib.so")
__CDinolib__ = CDLL("./dinolib.so")

# Hello world from the libraries
__CDinolib__._ZN8matchlib8matchlibEv()
__CDinolib__._ZN8inputlib8inputlibEv()
__CDinolib__._ZN6envlib6envlibEv()

def pyhandlerInit(N, firstDisplay): return c_int( __CDinolib__._ZN9pyhandler4initEjj( c_uint32(N), c_uint32(firstDisplay) ) )

# THIS DOES NOT WORK BTW (It doesnt work because of the static class issue)
def saveScreenshot(filename): 
    inputval = c_wchar_p(filename)
    rawoutput = __CDinolib__._ZN6envlib13dinoInterface14saveScreenshotEPc( inputval )
    returnval = c_int( rawoutput )
    return returnval