# CMakeList.txt : CMake project for Dinoai, include source and define
cmake_minimum_required(VERSION "3.17" FATAL_ERROR)

# Add source to this project's executable.
add_executable ( Dinoai "Dinoai.cpp" )

# === Build Executable and link libraries =============================================================
add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/Inputlib" )
add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/Matchlib" )
target_link_libraries( "Dinoai" LINK_PUBLIC "Inputlib" ) # LINK INPUTLIB TO EXECUTABLE
target_link_libraries( "Dinoai" LINK_PUBLIC "Matchlib" ) # LINK MATCHLIB TO EXECUTABLE
target_compile_options( "Dinoai" PUBLIC "-std=c++11")
target_link_options( "Dinoai" PUBLIC "-std=c++11")
# =====================================================================================================