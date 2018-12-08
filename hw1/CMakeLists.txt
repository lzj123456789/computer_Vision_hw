cmake_minimum_required(VERSION 2.8.4)
project(hw)
find_package(OpenCV REQUIRED)

set(SOURCE_FILES main.cpp)
add_executable(hw ${SOURCE_FILES})
add_definitions(-std=c++11)
target_link_libraries(hw ${OpenCV_LIBS}) 