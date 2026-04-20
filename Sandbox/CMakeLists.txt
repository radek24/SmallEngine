add_executable(Sandbox
        Source/Sandbox.cpp
        Source/Levels/TestLevel.cpp
        Source/Levels/TestLevel.h
        Source/Levels/MainMenuLevel.cpp
        Source/Levels/MainMenuLevel.h
        Source/Components/BouncyBallComponent.h
        Source/Systems/BouncyBallSystem.cpp
        Source/Systems/BouncyBallSystem.h
)

target_link_libraries(Sandbox PRIVATE SmallEngine)

if(WIN32)
    target_compile_options(Sandbox PRIVATE /utf-8)
    add_custom_command(TARGET Sandbox POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy -t
            $<TARGET_FILE_DIR:Sandbox>
            $<TARGET_RUNTIME_DLLS:Sandbox>
            $<TARGET_FILE:SmallEngine>
            COMMAND_EXPAND_LISTS
            VERBATIM
    )
endif()

add_custom_command(TARGET Sandbox POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/Resources"
        "$<TARGET_FILE_DIR:Sandbox>/Resources"
        VERBATIM
)