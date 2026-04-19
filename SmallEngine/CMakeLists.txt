add_subdirectory(Vendor/SDL3 EXCLUDE_FROM_ALL)

set(SDLIMAGE_VENDORED      ON  CACHE BOOL "" FORCE)
set(SDLIMAGE_INSTALL       OFF CACHE BOOL "" FORCE)

set(SDLIMAGE_PNG           ON  CACHE BOOL "" FORCE)
set(SDLIMAGE_JPG           ON  CACHE BOOL "" FORCE)
set(SDLIMAGE_BMP           OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_WEBP          OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_AVIF          OFF CACHE BOOL "" FORCE)
add_subdirectory(Vendor/SDL_image EXCLUDE_FROM_ALL)

set(SDLTTF_VENDORED        ON  CACHE BOOL "" FORCE)
set(SDLTTF_INSTALL         OFF CACHE BOOL "" FORCE)
add_subdirectory(Vendor/SDL_ttf EXCLUDE_FROM_ALL)

add_library(SmallEngine SHARED
        Source/Engine/Log/Log.cpp
        Source/ECS/Registry.cpp
        Source/Engine/App.cpp
        Source/Engine/Rendering/Window.cpp
        Source/Engine/Rendering/Renderer.cpp
        Source/Engine/Math/MathUtils.cpp
        Source/Engine/EventHandler.cpp
        Source/Engine/Level.cpp
        Source/Engine/Level.h
        Source/Engine/Math/Transform.h
        Source/Engine/Math/Rotator.h
        Source/ECS/ComponentPool.h
        Source/ECS/System.h
        Source/ECS/View.h
        Source/ECS/Systems/MovementSystem.cpp
        Source/ECS/Systems/MovementSystem.h
        Source/ECS/Components/TransformComponent.h
)

target_include_directories(SmallEngine PUBLIC
        ${CMAKE_SOURCE_DIR}/SmallEngine/Vendor
        ${CMAKE_SOURCE_DIR}/SmallEngine/Source
)

target_link_libraries(SmallEngine PUBLIC SDL3::SDL3)


target_compile_definitions(SmallEngine
        PRIVATE SE_BUILD_DLL
        INTERFACE SE_DLL
)

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

if(WIN32)
    target_compile_options(SmallEngine PRIVATE /utf-8)
    target_compile_definitions(SmallEngine PUBLIC PLATFORM_WINDOWS)
endif()

if(APPLE)
    target_compile_definitions(SmallEngine PUBLIC PLATFORM_MAC)
endif()

if(UNIX AND NOT APPLE)
    target_compile_definitions(SmallEngine PUBLIC PLATFORM_LINUX)
endif()
