
add_library(LichtEngine 
main.cpp
system/ServiceLocator.h
system/scripting/ScriptingEngine.cpp)
AddLightLibraries()

target_link_libraries(LichtEngine PUBLIC LichtEngine-Libraries)
target_copy_webgpu_binaries(LichtEngine)
