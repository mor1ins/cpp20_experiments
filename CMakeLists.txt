cmake_minimum_required(VERSION 3.17)
project(cpp20_experiments)

set(CMAKE_CXX_STANDARD 20)

add_executable(cpp20_experiments main.cpp compile_time_experiments.h)