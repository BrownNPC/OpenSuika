cmake_minimum_required(VERSION 3.25)
project(suika C)
include(FetchContent)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)
Set(FETCHCONTENT_QUIET FALSE)

# Dependencies

FetchContent_Declare(
  raylib
  URL https://github.com/raysan5/raylib/archive/refs/tags/5.5.tar.gz
)

FetchContent_Declare(
  stc
  GIT_REPOSITORY https://github.com/stclib/STC.git
  GIT_TAG v5.0
)

FetchContent_MakeAvailable(raylib stc)


file(GLOB_RECURSE SRC CONFIGURE_DEPENDS "src/*.c" "src/*.h" )
add_executable(${PROJECT_NAME} ${SRC})
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE
  src/
)


# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
target_include_directories(${PROJECT_NAME} PRIVATE
  ${stc_SOURCE_DIR}/include
)

# Web (Emscripten)
if (EMSCRIPTEN)
  set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
  target_link_options(${PROJECT_NAME} PRIVATE
    -sUSE_GLFW=3
    -sASYNCIFY
  )
endif()


if (PSP)
create_pbp_file(
  TARGET suika
  TITLE OpenSuika
  ICON_PATH "${CMAKE_CURRENT_SOURCE_DIR}/assets/icon.png"
  BUILD_PRX=1
  ENC_PRX=1
)
endif()
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR}) 
