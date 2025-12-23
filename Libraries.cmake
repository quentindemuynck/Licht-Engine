
include(FetchContent)

# SDL3
FetchContent_Declare(
  SDL3
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG release-3.2.28
  GIT_SHALLOW TRUE
  GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(SDL3)

# webgpu
FetchContent_Declare(
        webgpu
        GIT_REPOSITORY https://github.com/eliemichel/WebGPU-distribution
        GIT_TAG 17dcd42a7683355e7a40ac4e97e77f36dff5b5ab
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(webgpu)

# SDL3Webgpu
FetchContent_Declare(
        SDL3Webgpu
        GIT_REPOSITORY https://github.com/eliemichel/sdl3webgpu.git
        GIT_TAG 4fa9d70935e41c075f664b231ee10a64262a8ac7
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(SDL3Webgpu)

# GLM
FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 1.0.2
        GIT_SHALLOW TRUE
)
set(GLM_ENABLE_CXX_20 ON)
FetchContent_MakeAvailable(glm)
target_compile_definitions(glm PUBLIC
        GLM_FORCE_XYZW_ONLY
        GLM_FORCE_RADIANS
        GLM_FORCE_DEPTH_ZERO_TO_ONE
        GLM_FORCE_SILENT_WARNINGS
        GLM_ENABLE_EXPERIMENTAL
        GLM_EXT_INCLUDED
)

# IMGUI
FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG v1.92.1-docking
        GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(imgui)

# add_library(imgui)
# target_include_directories(imgui PUBLIC ${imgui_SOURCE_DIR})
# target_sources(imgui PRIVATE
#         ${imgui_SOURCE_DIR}/imgui.cpp
#         ${imgui_SOURCE_DIR}/imgui_draw.cpp
#         ${imgui_SOURCE_DIR}/imgui_widgets.cpp
#         ${imgui_SOURCE_DIR}/imgui_demo.cpp
#         ${imgui_SOURCE_DIR}/imgui_tables.cpp

#         ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl3.cpp
#         ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl3.h
#         ${imgui_SOURCE_DIR}/backends/imgui_impl_wgpu.cpp
#         ${imgui_SOURCE_DIR}/backends/imgui_impl_wgpu.h
# )
# target_compile_definitions(imgui PRIVATE IMGUI_IMPL_WEBGPU_BACKEND_DAWN)

# target_link_libraries(imgui PRIVATE
#     SDL3::SDL3
#     webgpu
# )

# spdlog
FetchContent_Declare(
        spdlog
        URL https://github.com/gabime/spdlog/archive/refs/tags/v1.15.1.zip
)
FetchContent_MakeAvailable(spdlog)


# tracy
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(TRACY_ENABLE OFF CACHE BOOL "" FORCE)
else()
    set(TRACY_ENABLE ON CACHE BOOL "" FORCE)
endif()

#option(TRACY_ENABLE " " ON)
option(TRACY_ON_DEMAND "" ON)
FetchContent_Declare(
        tracy
        URL https://github.com/wolfpld/tracy/archive/refs/tags/v0.13.0.zip
)
FetchContent_MakeAvailable(tracy)

# final
add_library(Licht-Engine-Libraries INTERFACE)
target_link_libraries(Licht-Engine-Libraries INTERFACE
        glm::glm
        # imgui
        spdlog
        TracyClient
        sdl3webgpu
        SDL3::SDL3
        webgpu
)
