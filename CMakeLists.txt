cmake_minimum_required(VERSION 3.24)

project(ThreeBodySimulation VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_executable(${PROJECT_NAME} ${SRC_FILES})
