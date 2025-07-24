set(CMAKE_CXX_STANDARD 17)
cmake_minimum_required(VERSION 3.10)
project(chess)

find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

add_executable(chess chess.cpp test.cpp gui.cpp PieceLoader.cpp)

target_link_libraries(chess sfml-graphics sfml-window sfml-system)
