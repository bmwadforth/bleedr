cmake_minimum_required(VERSION 3.13)
project(bleedr C CXX)

set(CMAKE_C_STANDARD 11)

if (WIN32)
    include_directories(lib/npcap/Include)
    link_directories(lib/npcap/Lib/x64)
endif()

if (UNIX)
    include_directories(lib/libpcap)
    link_directories(lib/libpcap)
    add_subdirectory(lib/libpcap)
    SET(LIBRARIES pcap)
endif()

add_executable(bleedr main.c)
target_link_libraries(bleedr ${LIBRARIES})