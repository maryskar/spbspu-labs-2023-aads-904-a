cmake_minimum_required(VERSION 3.24)
project(S5)

set(CMAKE_CXX_STANDARD 14)
include_directories(/home/sonex/cprojects/spbspu-labs-2023-aads-904-a/tarasenko.ksenia/common)
add_executable(S5 main.cpp
        /home/sonex/cprojects/spbspu-labs-2023-aads-904-a/tarasenko.ksenia/common/RedBlackTree.h readDataForTree.h
        readDataForTree.cpp printer.h
        /home/sonex/cprojects/spbspu-labs-2023-aads-904-a/tarasenko.ksenia/common/mathfunc.h
        summator.h)
