cmake_minimum_required(VERSION 3.13)
project(bleedr C)

set(CMAKE_C_STANDARD 11)

if (WIN32)
    include_directories(lib/libpcap)
    link_directories(lib/libpcap)
    add_subdirectory(lib/libpcap)
endif()

add_executable(bleedr main.c)
target_link_libraries(bleedr pcap)