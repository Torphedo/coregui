cmake_minimum_required(VERSION 3.13)
project(coregui C CXX)
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)

# Emit a compile_commands.json for use with clangd in LSPs
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

option(COREGUI_USE_IMGUI "Include ImGui-dependent code. Requires ImGui in your include paths.")

if (COREGUI_USE_IMGUI)
    set(extra_sources
        src/layer_imgui.cxx
    )
endif()

add_subdirectory(lib/glfw)
add_library(coregui STATIC
    src/gui_bootstrap.cxx
    src/gl_debug.c

    lib/glad/src/glad.c
    ${extra_sources}
)

target_include_directories(coregui PUBLIC ./src lib/glad/include lib/glfw/include)
target_link_libraries(coregui PUBLIC glfw)
