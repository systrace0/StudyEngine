cmake_minimum_required(VERSION 3.25...4.0)
project(TRACE VERSION 0.1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
option(ENABLE_ASAN "Enable AddressSanitizer" OFF)

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
endif()

include(cmake/Dependencies.cmake)
include(cmake/Targets.cmake)
include(cmake/Sanitizers.cmake)

# Declare targets first
add_library(TraceCore STATIC)
add_executable(TraceApp)

# Compiler warnings
if(MSVC)
    target_compile_options(TraceCore PRIVATE /W4 /FS)
    target_compile_options(TraceApp  PRIVATE /W4 /FS)
else()
    target_compile_options(TraceCore PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(TraceApp  PRIVATE -Wall -Wextra -Wpedantic)
endif()

enable_sanitizers(TraceApp)

# Copy assets next to executable after build
add_custom_command(TARGET TraceApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/App/shaders
    $<TARGET_FILE_DIR:TraceApp>/shaders
)

add_custom_command(TARGET TraceApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/App/assets
    $<TARGET_FILE_DIR:TraceApp>/assets
)

enable_testing()
add_subdirectory(Core)
add_subdirectory(App)
add_subdirectory(tests)