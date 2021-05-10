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

include_directories(lib/json/include)
link_directories(lib/json)
add_subdirectory(lib/json)

file (GLOB CPP_FILES src/**/*.cpp src/**/*.cc src/**/**/*.cpp src/**/**/*.cc src/io/json_writer.cpp)
file (GLOB C_FILES src/**/*.c src/**/**/*.c)
file (GLOB H_FILES include/**/*.h include/**/**/*.h)
set (SOURCE_FILES ${CPP_FILES} ${C_FILES} ${H_FILES})

add_executable(bleedr main.cpp ${SOURCE_FILES})
target_link_libraries(bleedr ${LIBRARIES})