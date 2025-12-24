function(AddLightLibraries)
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

    # entt
    FetchContent_Declare(
        entt
        GIT_REPOSITORY https://github.com/skypjack/entt.git
        GIT_TAG v3.16.0
        GIT_SHALLOW TRUE
    )
    FetchContent_MakeAvailable(entt)

    # # IMGUI
    # FetchContent_Declare(
    #     imgui
    #     GIT_REPOSITORY https://github.com/ocornut/imgui.git
    #     GIT_TAG v1.92.1-docking
    #     GIT_SHALLOW TRUE
    # )
    # FetchContent_MakeAvailable(imgui)

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

    # Reflection library from the allyway
    FetchContent_Declare(
        reflect
        GIT_REPOSITORY https://github.com/qlibs/reflect.git
        GIT_TAG 96b9548a6e114368a3ab22a674a0feab7da7cfd8
        GIT_SHALLOW TRUE
    )
    FetchContent_MakeAvailable(reflect)
    add_library(reflect_cpp20 INTERFACE)
    target_include_directories(reflect_cpp20 INTERFACE ${reflect_SOURCE_DIR} )

    # AngelScript
    FetchContent_Declare(
        angelscript
        GIT_REPOSITORY https://github.com/anjo76/angelscript.git
        GIT_TAG v2.38.0          
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
    )

    FetchContent_MakeAvailable(angelscript)
    
    set(AS_DISABLE_INSTALL ON CACHE BOOL "" FORCE)
    
    add_subdirectory(
            ${angelscript_SOURCE_DIR}/sdk/angelscript/projects/cmake
            ${angelscript_BINARY_DIR}/as_build
    )

    # AngelScript add-ons 
    add_library(angelscript_addons STATIC
        ${angelscript_SOURCE_DIR}/sdk/add_on/scriptstdstring/scriptstdstring.cpp
        ${angelscript_SOURCE_DIR}/sdk/add_on/scriptarray/scriptarray.cpp
        ${angelscript_SOURCE_DIR}/sdk/add_on/scriptdictionary/scriptdictionary.cpp
        ${angelscript_SOURCE_DIR}/sdk/add_on/scriptbuilder/scriptbuilder.cpp
    )

    target_include_directories(angelscript_addons PUBLIC
        ${angelscript_SOURCE_DIR}/sdk/angelscript/include 
        ${angelscript_SOURCE_DIR}/sdk/add_on/scriptstdstring
        ${angelscript_SOURCE_DIR}/sdk/add_on/scriptarray
        ${angelscript_SOURCE_DIR}/sdk/add_on/scriptdictionary
        ${angelscript_SOURCE_DIR}/sdk/add_on/scriptbuilder
    )

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

    # ENet used for UDP based net
    FetchContent_Declare(
            enet
            URL https://github.com/zpl-c/enet/archive/refs/tags/v2.6.5.zip
    )
    FetchContent_MakeAvailable(enet)

    # Libsodium used for network encryption
    FetchContent_Declare(
            libsodium
            GIT_REPOSITORY https://github.com/robinlinden/libsodium-cmake.git
            GIT_TAG master
            GIT_SHALLOW TRUE
    )
    FetchContent_MakeAvailable(libsodium)

    # LZ4 fast compression for network
    FetchContent_Declare(
            lz4
            GIT_REPOSITORY https://github.com/lz4/lz4.git
            GIT_TAG v1.10.0
            GIT_SHALLOW TRUE
            GIT_PROGRESS TRUE
    )
    FetchContent_MakeAvailable(lz4)

    add_library(lz4 STATIC
            ${lz4_SOURCE_DIR}/lib/lz4.c
            ${lz4_SOURCE_DIR}/lib/lz4hc.c
    )

    target_include_directories(lz4 PUBLIC
            ${lz4_SOURCE_DIR}/lib
    )

    target_compile_definitions(lz4 PUBLIC
            LZ4_DISABLE_DEPRECATE_WARNINGS
    )

    # final
    add_library(LichtEngine-Libraries INTERFACE)
    target_link_libraries(LichtEngine-Libraries INTERFACE
            glm::glm
            # imgui
            angelscript
            angelscript_addons # to be able to use std::string and no manual conversion to cstyle string
            spdlog
            TracyClient
            sdl3webgpu
            SDL3::SDL3
            webgpu
            EnTT::EnTT
            lz4
            enet::enet_static
            sodium
            reflect_cpp20
    )
endfunction()
