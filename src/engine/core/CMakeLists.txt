add_library(LichtEngine-core)

file(GLOB src "src/*")
target_sources(LichtEngine-core PRIVATE ${src})
target_include_directories(LichtEngine-core PUBLIC include)
target_link_libraries(LichtEngine-core PUBLIC LichtEngine-Libraries)
