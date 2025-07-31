set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "-g")
cmake_minimum_required(VERSION 3.10)
project(chess)

find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

add_executable(chess chess.cpp test.cpp gui.cpp PieceLoader.cpp)

target_link_libraries(chess sfml-graphics sfml-window sfml-system)
