add_executable(EngineTests
        ${CMAKE_SOURCE_DIR}/SmallEngine/Vendor/doctest/doctest.cpp
        ECS/ComponentPoolTests.cpp
        ECS/RegistryTests.cpp
        Math/Vector2fTests.cpp
        Math/RotatorTests.cpp
        Math/ColorTests.cpp
        ECS/ViewTests.cpp
        Core/SignalManagerTests.cpp
        Core/SettingManagerTests.cpp
)


target_include_directories(EngineTests PRIVATE
        ${CMAKE_SOURCE_DIR}/SmallEngine/Source
        ${CMAKE_SOURCE_DIR}/SmallEngine/Vendor
)

if(WIN32)
    target_compile_options(EngineTests PRIVATE /utf-8)
endif()

target_link_libraries(EngineTests PRIVATE SmallEngine)

enable_testing()
add_test(NAME EngineTests COMMAND EngineTests)
