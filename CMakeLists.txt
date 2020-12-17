cmake_minimum_required(VERSION 3.0.0)
project(outlier_correction)
add_definitions(-std=c++11)

include_directories(
  src
)

add_executable(demo test/demo.cpp src/correct_outlier.cpp)

target_link_libraries(demo
)