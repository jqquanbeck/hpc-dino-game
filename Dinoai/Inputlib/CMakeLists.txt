# Overview
cmake_minimum_required(VERSION "3.17" FATAL_ERROR)
add_library( Inputlib
    STATIC "${CMAKE_CURRENT_SOURCE_DIR}/Inputlib.cpp" 
)

# Scan for libX11
include( "FindX11" )

# === CONFIGURE TARGET MATCHLIB =======================================================
target_include_directories( Inputlib
    PUBLIC "${X11_INCLUDE_DIR}"
)  
target_link_libraries( Inputlib
    "${X11_LIBRARIES}"
)
target_compile_options( Inputlib
    PUBLIC "-lX11" 
    PUBLIC "-lXtst"
)
target_link_options( Inputlib
    PUBLIC "-lX11" 
    PUBLIC "-lXtst"
)
# =====================================================================================