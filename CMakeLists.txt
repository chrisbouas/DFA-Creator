project(DFA-Creator)
cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 14)

file(GLOB srcs *.cpp *.h)

add_executable(${PROJECT_NAME} ${srcs})