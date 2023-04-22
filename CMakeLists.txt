cmake_minimum_required(VERSION 3.14)

project(IMG_Calibration)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

link_directories(${OpenCV_LIBRARY_DIRS})

add_executable(IMG_Calibration claibration_img.cpp)

target_link_libraries(IMG_Calibration ${OpenCV_LIBS})