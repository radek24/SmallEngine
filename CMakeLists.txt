cmake_minimum_required(VERSION 3.29)
project(SmallEngine)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Vendor/SDL2)

add_executable(SmallEngine
        Source/Log/Log.cpp
        Source/Log/Log.h
        Source/EntryPoint.cpp)

target_include_directories(SmallEngine PRIVATE
        ${CMAKE_SOURCE_DIR}/Vendor
        ${CMAKE_SOURCE_DIR}/Source
        ${CMAKE_SOURCE_DIR}/Vendor/SDL2/include
)

target_link_libraries(SmallEngine PRIVATE SDL2::SDL2 SDL2::SDL2main)


if(WIN32)
    target_compile_options(SmallEngine PRIVATE /utf-8)
endif()
