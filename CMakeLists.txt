cmake_minimum_required(VERSION 3.6)
project(RubiksCube)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(SOURCE_FILES main.cpp display.cpp display.h RubiksCube.cpp RubiksCube.h constants.h usefull.h solve.cpp solve.h)
add_executable(RubiksCube ${SOURCE_FILES} main.cpp display.cpp display.h RubiksCube.cpp RubiksCube.h constants.h usefull.h solve.cpp solve.h)

target_link_libraries(${PROJECT_NAME} GL GLU glut)