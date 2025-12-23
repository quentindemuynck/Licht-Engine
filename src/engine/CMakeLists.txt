
add_library(LichtEngine
    main.cpp
)

add_subdirectory(core)
add_subdirectory(renderer)
add_subdirectory(scripting)

target_link_libraries(LichtEngine PUBLIC LichtEngine-core)
target_link_libraries(LichtEngine PUBLIC LichtEngine-renderer)
target_link_libraries(LichtEngine PUBLIC LichtEngine-scripting)
