from ctypes import *
import sys

cdll.LoadLibrary("./dinolib.so")
__CDinolib__ = CDLL("./dinolib.so")

# Hello world from the libraries
# __CDinolib__._ZN8matchlib8matchlibEv()
# __CDinolib__._ZN8inputlib8inputlibEv()
# __CDinolib__._ZN6envlib6envlibEv()

def pyhandlerInit( N, firstDisplay ): 
    return c_int( __CDinolib__._ZN9pyhandler4initEjj( c_uint32(N), c_uint32(firstDisplay) ) )

def pyhandlerGetScore( i ):
    score = c_int32()
    c_int( __CDinolib__._ZN9pyhandler8getScoreEjRj( c_uint32(i), byref(score) ) )
    return score


# === this one ======
def pyhandlerGetObservation( i ):
    getObservation = __CDinolib__._ZN6envlib13dinoInterface14getObservationEPj
    getObservation.argtypes = ( c_uint32, c_uint32 * 13 )
    getObservation.restype = c_int
    observation = ( c_uint32 * 13 )()
    getObservation( c_uint32(i), observation )
    result = [observation[i] for i in range(13)]
    return result
# ====================

def pyhandlerSetAction( i, action ):
    return c_int( __CDinolib__._ZN9pyhandler9setActionEjj( c_uint32(i), c_uint32(action) ) )

# THIS DOES NOT WORK BTW (It doesnt work because of the static class issue)
def saveScreenshot(filename): 
    inputval = c_wchar_p(filename)
    rawoutput = __CDinolib__._ZN6envlib13dinoInterface14saveScreenshotEPc( inputval )
    returnval = c_int( rawoutput )
    return returnval

# def envlib():
#     getObservation = __CDinolib__._ZN6envlib6envlibEv
#     getObservation.argtypes = ( c_uint32, c_uint32 * 3 )
#     getObservation.restype = c_int
#     observation = ( c_uint32 * 3 )()
#     getObservation( observation )
#     result = [observation[i] for i in range(13)]
#     return result