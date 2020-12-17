cmake_minimum_required(VERSION 3.0.0)
project(outlier_correction)
add_definitions(-std=c++11)

include_directories(
  src
)

add_executable(demo_signal_processing test/demo_signal_processing.cpp src/correct_outlier.cpp)
add_executable(demo_line_fitting test/demo_line_fitting.cpp src/correct_outlier.cpp)