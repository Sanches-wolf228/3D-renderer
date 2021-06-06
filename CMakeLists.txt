cmake_minimum_required(VERSION 3.16)
project(3D-Render)

set(CMAKE_CXX_STANDARD 17)

add_executable(3D-Render screen.cpp renderer.cpp test1.cpp application.cpp main.cpp)

find_package(SFML COMPONENTS system window graphics REQUIRED)
target_link_libraries(3D-Render sfml-system sfml-window sfml-graphics)
include_directories(${SFML_INCLUDE_DIRS})
