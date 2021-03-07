cmake_minimum_required(VERSION 3.17)
project(opencv)

set(CMAKE_CXX_STANDARD 17)
find_package(OpenCV REQUIRED)

add_executable(opencv_project pts.cpp)

target_link_libraries(opencv_project ${OpenCV_LIBS})