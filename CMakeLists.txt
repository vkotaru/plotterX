cmake_minimum_required(VERSION 3.3.2)
project (HELLO)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#find_package(OpenGL REQUIRED)
##find_package(GLUT)
#include_directories( ${OPENGL_INCLUDE_DIRS} )

include_directories(include)

add_subdirectory(simplewindow)

set(SRCS
        src/main.cpp
        src/PlotterX.cpp
        src/UIInput.cpp
        src/UIUtilities.cpp
        src/UserInterface.cpp
        src/UIVariablesInput.cpp
        src/ysglfontdata.c)


add_executable(plotterX ${SRCS})
target_link_libraries(plotterX fssimplewindow)
target_include_directories(plotterX PRIVATE ${CMAKE_SOURCE_DIR}/include)
