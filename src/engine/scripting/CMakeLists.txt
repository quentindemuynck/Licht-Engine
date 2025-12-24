add_library(LichtEngine-scripting)

file(GLOB src "src/*")
target_sources(LichtEngine-scripting PRIVATE ${src})
target_include_directories(LichtEngine-scripting PUBLIC include)
target_link_libraries(LichtEngine-scripting PUBLIC LichtEngine-Libraries)

add_custom_command(TARGET LichtEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/src/game
            $<TARGET_FILE_DIR:LichtEngine>/game
)
