add_library(LichtEngine-net)

file(GLOB src "src/*")
target_sources(LichtEngine-net PRIVATE ${src})
target_include_directories(LichtEngine-net PUBLIC include)
target_link_libraries(LichtEngine-net PUBLIC LichtEngine-Libraries)
