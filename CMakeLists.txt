project(DFA-Creator)
set(CMAKE_CXX_STANDARD 11)

file(GLOB srcs *.cpp *.h)

add_executable(${PROJECT_NAME} ${srcs})