
add_executable(LichtEngine
    main.cpp
)

add_subdirectory(core)
add_subdirectory(renderer)
add_subdirectory(scripting)

target_link_libraries(LichtEngine PUBLIC LichtEngine-core)
target_link_libraries(LichtEngine PUBLIC LichtEngine-renderer)
target_link_libraries(LichtEngine PUBLIC LichtEngine-scripting)

add_custom_command(TARGET LichtEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/src/game
            $<TARGET_FILE_DIR:LichtEngine>/game
)