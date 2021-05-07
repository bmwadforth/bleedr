cmake_minimum_required(VERSION 3.13)
project(bleedr)

#set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

if (WIN32)
    include_directories(lib/npcap/Include)
    link_directories(lib/npcap/Lib)
    SET(LIBRARIES wpcap)
endif()

if (UNIX)
    include_directories(lib/libpcap)
    link_directories(lib/libpcap)
    add_subdirectory(lib/libpcap)
    SET(LIBRARIES pcap)
endif()

file(GLOB bleedr_src "include/**/*.h" "src/**/*.cpp" "src/**/*.c")
add_executable(bleedr main.cpp ${bleedr_src} src/common/interface.c)
target_link_libraries(bleedr ${LIBRARIES})