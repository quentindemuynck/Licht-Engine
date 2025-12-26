add_library(LichtEngine-scripting)

file(GLOB src "src/*")
target_sources(LichtEngine-scripting PRIVATE ${src})
target_include_directories(LichtEngine-scripting PUBLIC include)
target_link_libraries(LichtEngine-scripting PUBLIC LichtEngine-Libraries)


