cmake_minimum_required(VERSION 3.25...4.0)
project(Engine VERSION 0.1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  # Don't allow gcc/msvc extensions. Stay portable.

# ── Dependencies ──────────────────────────────────────────────────────────────
include(FetchContent)

# GLFW - windowing and input
# GIT_TAG pins to an exact version. Never use "master" in engine code.
# If upstream breaks something, your project keeps working until YOU decide to update.
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        3.4
    GIT_SHALLOW    TRUE  # Only fetch the tagged commit, not full history. Faster.
)

# These options turn off things we don't need from GLFW's own CMakeLists
# Docs, tests, examples - not our problem to build
set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(glfw)

# ── GLAD (owned source, not fetched) ─────────────────────────────────────────
# We treat glad as a tiny internal static library.
# This is cleaner than just dumping glad.c into your main sources.
add_library(glad STATIC
    external/glad/src/glad.c
)
target_include_directories(glad PUBLIC
    external/glad/include
)

# ── Engine sources ─────────────────────────────────────────────────────────
add_executable(${PROJECT_NAME})

# Copy shaders folder next to the built executable after build
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/shaders
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders
)

# ── Compiler warnings ─────────────────────────────────────────────────────────
# This is not optional. Warnings are your first line of defense.
# A senior engineer with zero warnings is more productive than one with 200 suppressed ones.
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /FS)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_subdirectory(src)