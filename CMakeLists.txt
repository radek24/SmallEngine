cmake_minimum_required(VERSION 3.28)
project(SmallEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(Vendor/SDL3 EXCLUDE_FROM_ALL)

add_executable(SmallEngine
        Source/EntryPoint.cpp
        Source/Log/Log.cpp
        Source/ECS/Registry.h
        Source/ECS/Entity.h
        Source/ECS/Registry.cpp
        Source/Math/Vector.h
        Source/ECS/Components/TransformComponent.h
        Source/Math/MathForward.h
        Source/ECS/Components/VelocityComponent.h
        Source/Core/DebugBreaks.h
)

target_include_directories(SmallEngine PRIVATE
        ${CMAKE_SOURCE_DIR}/Vendor
        ${CMAKE_SOURCE_DIR}/Source
)

target_link_libraries(SmallEngine PRIVATE SDL3::SDL3)

if(WIN32)
    target_compile_options(SmallEngine PRIVATE /utf-8)

    add_custom_command(TARGET SmallEngine POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy -t
            $<TARGET_FILE_DIR:SmallEngine>
            $<TARGET_RUNTIME_DLLS:SmallEngine>
            COMMAND_EXPAND_LISTS
            VERBATIM
    )

endif()

add_custom_command(TARGET SmallEngine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/Resources"
        "$<TARGET_FILE_DIR:SmallEngine>/Resources"
        VERBATIM
)