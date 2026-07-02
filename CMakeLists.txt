cmake_minimum_required(VERSION 3.20)
project(Solaris_Engine VERSION 0107.26)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)

include_directories(include)

####Executable####
add_executable(Solaris_Engine
src/main.cpp
src/glad.c
src/shader.cpp
include/shader.hpp
)
##################

target_include_directories(Solaris_Engine PRIVATE include)
target_link_libraries(Solaris_Engine glfw OpenGL::GL dl glm::glm)
