cmake_minimum_required(VERSION 3.5)
project(game-project)

option(GLFW_BUILD_DOCS ON)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS ON)

include_directories(lib/GLFW/include)
include_directories(lib/glm)
include_directories(lib/glad/include)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/GLFW)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/glm)

add_executable(game-project src/main.cpp src/game/engine.cpp src/game/engine.h lib/glad/src/glad.c lib/glad/include/glad/glad.h)
target_link_libraries(game-project glfw)