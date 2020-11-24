# CMakeList.txt : CMake project for Matchlib, include source and define
cmake_minimum_required(VERSION "3.17" FATAL_ERROR)
project(Matchlib2)
add_library( Matchlib
    STATIC "${CMAKE_CURRENT_SOURCE_DIR}/Matchlib.cpp" 
)

# Scan for OpenCV
#set( CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${Dinoai_SOURCE_DIR}/External" )
find_package( OpenCV REQUIRED )


add_executable(MatchTest Match.cpp)

# === CONFIGURE TARGET MATCHLIB =======================================================
target_include_directories( Matchlib
    PUBLIC "${OpenCV_INCLUDE_DIRS}"
)  
include_directories(${OpenCV_INCLUDE_DIRS}
)  
target_link_libraries( Matchlib
    "${OpenCV_LIBRARIES}"
)
target_compile_options( Matchlib
    PUBLIC ""
)
target_link_options( Matchlib
    PUBLIC ""
)
# =====================================================================================


