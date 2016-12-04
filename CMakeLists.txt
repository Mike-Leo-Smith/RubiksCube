cmake_minimum_required(VERSION 3.5)
project(RubiksCube)

if (WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -static -O3 -Wl,--subsystem,windows")
elseif (APPLE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -v")
endif ()

set(SOURCE_FILES main.cpp RubiksCube.cpp RubiksCube.h constants.h usefull.h solve.cpp solve.h display.h display.cpp)
add_executable(RubiksCube ${SOURCE_FILES} main.cpp RubiksCube.cpp RubiksCube.h constants.h usefull.h solve.cpp solve.h display.h display.cpp)

if (WIN32)
	target_link_libraries(${PROJECT_NAME} glfw3 opengl32 glu32)
elseif (APPLE)
	target_link_libraries(${PROJECT_NAME} glfw3)
endif ()