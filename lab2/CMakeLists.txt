cmake_minimum_required(VERSION 3.10)
project(Calculator)

add_library(calculator_lib STATIC calculator.cpp)

add_executable(calculator_app main.cpp)

target_link_libraries(calculator_app calculator_lib)
