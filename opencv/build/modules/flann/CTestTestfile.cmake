# CMake generated Testfile for 
# Source directory: /home/joel/Documents/HPC/hpc-dino-game/opencv/opencv-master/modules/flann
# Build directory: /home/joel/Documents/HPC/hpc-dino-game/opencv/build/modules/flann
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(opencv_test_flann "/home/joel/Documents/HPC/hpc-dino-game/opencv/build/bin/opencv_test_flann" "--gtest_output=xml:opencv_test_flann.xml")
set_tests_properties(opencv_test_flann PROPERTIES  LABELS "Main;opencv_flann;Accuracy" WORKING_DIRECTORY "/home/joel/Documents/HPC/hpc-dino-game/opencv/build/test-reports/accuracy" _BACKTRACE_TRIPLES "/home/joel/Documents/HPC/hpc-dino-game/opencv/opencv-master/cmake/OpenCVUtils.cmake;1640;add_test;/home/joel/Documents/HPC/hpc-dino-game/opencv/opencv-master/cmake/OpenCVModule.cmake;1310;ocv_add_test_from_target;/home/joel/Documents/HPC/hpc-dino-game/opencv/opencv-master/cmake/OpenCVModule.cmake;1074;ocv_add_accuracy_tests;/home/joel/Documents/HPC/hpc-dino-game/opencv/opencv-master/modules/flann/CMakeLists.txt;2;ocv_define_module;/home/joel/Documents/HPC/hpc-dino-game/opencv/opencv-master/modules/flann/CMakeLists.txt;0;")