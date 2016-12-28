cmake_minimum_required(VERSION 3.6)
project(wiznet)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/rpi.h src/swig_wrapper.c src/rpi.c src/Platform/ff.h src/Platform/ff.c src/swig_wrapper.h src/commons.h src/commons.c)
add_executable(wiznet ${SOURCE_FILES})