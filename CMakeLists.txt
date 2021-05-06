cmake_minimum_required(VERSION 3.13)
project(bleedr C CXX)

set(CMAKE_C_STANDARD 11)

if (WIN32)
    include_directories(lib/npcap/Include)
    #add_library(pcap STATIC ${CMAKE_SOURCE_DIR}/lib/npcap/Lib/wpcap.lib ${CMAKE_SOURCE_DIR}/lib/npcap/Lib/Packet.lib)
    add_library(pcap OBJECT ${CMAKE_SOURCE_DIR}/lib/npcap/Lib/wpcap.lib ${CMAKE_SOURCE_DIR}/lib/npcap/Lib/Packet.lib)
endif()

if (UNIX)
    include_directories(lib/libpcap)
    link_directories(lib/libpcap)
    add_subdirectory(lib/libpcap)
endif()

add_executable(bleedr main.c)
target_link_libraries(bleedr pcap)