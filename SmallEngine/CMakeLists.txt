add_subdirectory(Vendor/SDL3 EXCLUDE_FROM_ALL)

add_library(SmallEngine SHARED
        Source/Engine/Log/Log.cpp
        Source/ECS/Registry.cpp
        Source/ECS/Components/VelocityComponent.h
        Source/Engine/App.cpp
        Source/Engine/Rendering/Window.cpp
        Source/Engine/Rendering/Renderer.cpp
        Source/Engine/Math/MathUtils.cpp
        Source/Engine/EventHandler.cpp
        Source/Engine/Level.cpp
        Source/Engine/Level.h
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
    target_compile_definitions(SmallEngine PRIVATE PLATFORM_WINDOWS)
elseif(APPLE)
    target_compile_definitions(SmallEngine PRIVATE PLATFORM_MAC)
endif()