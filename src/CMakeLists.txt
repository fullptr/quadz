cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS}")
set(CMAKE_STATIC_LINKER_FLAGS "${CMAKE_STATIC_LINKER_FLAGS}")

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

add_executable(quadz
    quadz.m.cpp
    renderer.cpp
    game_grid.cpp

    core/mouse.cpp
    core/shader.cpp
    core/texture.cpp
    core/utility.cpp
    core/window.cpp
)

target_include_directories(quadz PUBLIC .)

target_link_libraries(quadz PRIVATE
    glfw
    glad::glad
    glm::glm
)