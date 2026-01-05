cmake_minimum_required(VERSION 3.11) 
project(suika LANGUAGES C)

# Project settings
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) 

set(RAYLIB_VERSION 5.5) 

# Use CONFIGURE_DEPENDS so CMake regenerates when source files change
file(GLOB SRC_FILES CONFIGURE_DEPENDS
    ${CMAKE_SOURCE_DIR}/src/*.c
    ${CMAKE_SOURCE_DIR}/src/*.h
)


if (SRC_FILES)
    add_executable(${PROJECT_NAME} ${SRC_FILES})
else()
    message(FATAL_ERROR "No sources found in ${CMAKE_SOURCE_DIR}/src")
endif()

# ---- raylib dependency (find or fetch) ----
find_package(raylib ${RAYLIB_VERSION} QUIET) # try system or installed raylib first
if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        raylib
        URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
        DOWNLOAD_EXTRACT_TIMESTAMP OFF
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED)
        set(FETCHCONTENT_QUIET NO) # show progress when fetching
        FetchContent_MakeAvailable(raylib)
    endif()
endif()

# After FetchContent or find_package, link raylib
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# ---- Platform / Web handling ----
# Accept -DPLATFORM=Web or auto-detect Emscripten
if (EMSCRIPTEN)
    set(PLATFORM "Web" CACHE STRING "Target platform")
endif()

if (PLATFORM STREQUAL "Web")
    # instruct Emscripten to emit an HTML file and set useful flags
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY -s GL_ENABLE_GET_PROC_ADDRESS=1")
endif()

if (APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE "-framework IOKit" "-framework Cocoa" "-framework OpenGL")
endif()

# ---- Compiler warnings ----
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /permissive-)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

# ---- Install (optional) ----
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

# ---- Helpful summary ----
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "C standard: ${CMAKE_C_STANDARD}")
message(STATUS "Raylib version requested: ${RAYLIB_VERSION}")
message(STATUS "Platform: ${PLATFORM}")


