cmake_minimum_required(VERSION 3.27)
project(TCP_server)

set(CMAKE_CXX_STANDARD 17)

add_executable(TCP_server main.cpp)

target_link_libraries(TCP_server Ws2_32)

