cmake_minimum_required(VERSION 3.16)
project(S2)

set(CMAKE_CXX_STANDARD 14)

include_directories(../common)
set(SOURCE_FILES
        ../common/dictionary.h
        ../common/labList1.h)
add_executable(S2 ${SOURCE_FILES} main.cpp)

include_directories(.)
