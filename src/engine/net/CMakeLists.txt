add_library(LichtEngine-net
        src/server.cpp
        include/server.h
        src/Test.cpp
        src/Test.h
        src/test.cpp
        src/test.h
        src/client.cpp
        include/client.h)

file(GLOB src "src/*")
target_sources(LichtEngine-net PRIVATE ${src})
target_include_directories(LichtEngine-net PUBLIC include)
target_link_libraries(LichtEngine-net PUBLIC LichtEngine-Libraries)
