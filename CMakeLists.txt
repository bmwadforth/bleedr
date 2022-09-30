cmake_minimum_required(VERSION 3.13)
project(bleedr)

set(CMAKE_CXX_STANDARD 20)
include_directories(include)

if (WIN32)
    include_directories(lib/npcap/Include)
    link_directories(lib/npcap/Lib)
    SET(LIBRARIES wpcap)
endif()

if (UNIX AND NOT APPLE)
    include_directories(lib/libpcap)
    link_directories(lib/libpcap)
    add_subdirectory(lib/libpcap)
    link_libraries(stdc++fs)
    SET(GCC_COVERAGE_LINK_FLAGS "-lgcov")
endif()

if (APPLE)
    find_library(LIBRARIES NAMES pcap)
endif()

add_subdirectory(lib/json)
include_directories(lib/json/include)

file (GLOB CPP_FILES src/**/*.cpp src/**/*.cc src/**/**/*.cpp src/**/**/*.cc src/io/json_writer.cpp)
file (GLOB C_FILES src/**/*.c src/**/**/*.c)
file (GLOB H_FILES include/**/*.h include/**/**/*.h)
set (SOURCE_FILES ${CPP_FILES} ${C_FILES} ${H_FILES})

SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

add_executable(bleedr main.cpp ${SOURCE_FILES})
target_link_libraries(bleedr ${LIBRARIES} nlohmann_json::nlohmann_json)