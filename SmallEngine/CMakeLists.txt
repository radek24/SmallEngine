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

set(SDL2MIXER_INSTALL OFF)
set(SDL2MIXER_SAMPLES OFF)
set(SDL2MIXER_VENDORED ON)
add_subdirectory(Vendor/SDL_mixer EXCLUDE_FROM_ALL)

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
        Source/ECS/Components/TransformComponent.h
        Source/ECS/Components/SpriteComponent.h
        Source/Engine/Rendering/TextureManager.cpp
        Source/Engine/Rendering/TextureManager.h
        Source/ECS/Systems/RenderSystem.cpp
        Source/ECS/Systems/RenderSystem.h
        Source/ECS/Components/CameraComponent.h
        Source/ECS/Systems/SimpleControllerSystem.cpp
        Source/ECS/Systems/SimpleControllerSystem.h
        Source/ECS/Components/SimpleKeyboardControllerComponent.h
        Source/ECS/Components/LifetimeComponent.h
        Source/ECS/Systems/LifetimeSystem.cpp
        Source/ECS/Systems/LifetimeSystem.h
        Source/Engine/Rendering/FontManager.cpp
        Source/Engine/Rendering/FontManager.h
        Source/ECS/Systems/UIRenderSystem.h
        Source/ECS/Systems/UIRenderSystem.cpp
        Source/ECS/Components/UITextComponent.h
        Source/ECS/Systems/RotatorSystem.h
        Source/ECS/Components/RotatorComponent.h
        Source/ECS/Components/UIButtonComponent.h
        Source/ECS/Systems/DebugDrawTransformSystem.cpp
        Source/ECS/Systems/DebugDrawTransformSystem.h
        Source/ECS/Components/ColliderComponent.h
        Source/ECS/Systems/UIButtonSystem.h
        Source/Engine/Math/CollisionUtils.cpp
        Source/Engine/Math/CollisionUtils.h
        Source/ECS/Systems/RotatorSystem.cpp
        Source/ECS/Systems/UIButtonSystem.cpp
        Source/ECS/Systems/DebugDrawUISystem.cpp
        Source/ECS/Systems/DebugDrawUISystem.h
        Source/ECS/Prefabs/Prefab.h
        Source/ECS/Systems/DebugStatsSystem.cpp
        Source/ECS/Systems/DebugStatsSystem.h
        Source/ECS/Systems/UITextEffectSystem.cpp
        Source/ECS/Systems/UITextEffectSystem.h
        Source/ECS/Components/RainbowTextEffectComponent.h
        Source/ECS/Components/ShakeComponent.h
        Source/ECS/Systems/ShakerSystem.cpp
        Source/ECS/Systems/ShakerSystem.h
        Vendor/Noise/FastNoiseLite.h
        Source/ECS/Components/PlaySoundRequestComponent.h
        Source/ECS/Components/AudioConfigComponent.h
        Source/ECS/Systems/SoundSystem.cpp
        Source/ECS/Systems/SoundSystem.h
        Source/ECS/Components/ParticleComponent.h
        Source/ECS/Systems/ParticleSystem.cpp
        Source/ECS/Systems/ParticleSystem.h
        Source/Engine/SoundManager.cpp
        Source/Engine/SoundManager.h
        Source/ECS/Serialization.h
        Source/Engine/SignalManager.cpp
        Source/Engine/SignalManager.h
)

target_include_directories(SmallEngine PUBLIC
        ${CMAKE_SOURCE_DIR}/SmallEngine/Vendor
        ${CMAKE_SOURCE_DIR}/SmallEngine/Source
)

target_link_libraries(SmallEngine PUBLIC
        SDL3::SDL3
        SDL3_image::SDL3_image
        SDL3_ttf::SDL3_ttf
        SDL3_mixer::SDL3_mixer
)


target_compile_definitions(SmallEngine
        PRIVATE SE_BUILD_DLL
        INTERFACE SE_DLL
)

if(WIN32)
    target_compile_options(SmallEngine PRIVATE /utf-8)
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

# Build type
target_compile_definitions(SmallEngine PUBLIC
        $<$<CONFIG:Debug>:SE_DEBUG>
        $<$<CONFIG:Release>:SE_RELEASE>
)