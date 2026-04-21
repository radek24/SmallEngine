cmake_minimum_required(VERSION 3.28)
project(SmallEngineWorkspace LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<CONFIG>)

add_subdirectory(SmallEngine)
add_subdirectory(Sandbox)