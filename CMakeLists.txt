cmake_minimum_required(VERSION 3.5)
project(RubiksCube)

if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -static -O3 -Wl,--subsystem,windows")
elseif (LINUX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -static -O3")
endif ()

set(SOURCE_FILES main.cpp RubiksCube.cpp RubiksCube.h constants.h usefull.h solve.cpp solve.h display.h display.cpp)
add_executable(RubiksCube ${SOURCE_FILES} main.cpp RubiksCube.cpp RubiksCube.h constants.h usefull.h solve.cpp solve.h display.h display.cpp)

if (WIN32)
    target_link_libraries(${PROJECT_NAME} glfw3 opengl32 glu32)
elseif (LINUX)
    target_link_libraries(${PROJECT_NAME} glfw3 GL GLU)
endif ()