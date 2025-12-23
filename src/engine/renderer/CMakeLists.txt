add_library(LichtEngine-renderer)

file(GLOB src "src/*")
target_sources(LichtEngine-renderer PRIVATE ${src})
target_include_directories(LichtEngine-renderer PUBLIC include)
target_link_libraries(LichtEngine-renderer PUBLIC LichtEngine-Libraries)
target_link_libraries(LichtEngine-renderer PUBLIC LichtEngine-core)

target_copy_webgpu_binaries(LichtEngine-renderer)
