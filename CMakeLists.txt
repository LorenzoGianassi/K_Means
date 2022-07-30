cmake_minimum_required(VERSION 3.17)
project(MidTerm_PC)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")

# TO CHANGE THE TYPE OF EXECUTION COMMENT/UNCOMMENT ONE OF THE FOLLOWING LINES:
add_executable(MidTerm_PC sequential_main.cpp Point.h Cluster.h )
#add_executable(MidTerm_PC parallel_main.cpp Point.h Cluster.h)

