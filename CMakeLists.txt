cmake_minimum_required(VERSION 3.25...4.0)
project(TRACE VERSION 0.1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  # Don't allow gcc/msvc extensions. Stay portable.
option(ENABLE_ASAN "Enable AddressSanitizer (and UBSan on non-MSVC)" OFF)

include(cmake/Dependencies.cmake)
include(cmake/Targets.cmake)

# ── Engine executable ──────────────────────────────────────────────────────────
add_executable(${PROJECT_NAME})

include(cmake/Sanitizers.cmake)
enable_sanitizers(${PROJECT_NAME})

# Copy shaders folder next to the built executable after build
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/shaders
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders
)

# ── Compiler warnings ──────────────────────────────────────────────────────────
# Not optional. Warnings are your first line of defense.
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /FS)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_subdirectory(src)