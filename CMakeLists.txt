cmake_minimum_required(VERSION 3.27)
project(CA2)

set(CMAKE_CXX_STANDARD 17)

add_executable(CA2 main.cpp
        Board.cpp
        Bug.cpp
        Crawler.cpp
        Hopper.cpp
        bugs.txt)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML-2.6.1/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/SFML-2.6.1/include/SFML)
target_link_libraries(CA2 sfml-system sfml-window sfml-graphics sfml-audio)
