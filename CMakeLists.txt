cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)

project(SnakeGame)
add_subdirectory(SDL2)

add_executable(SnakeGame src/main.cpp src/game.cpp src/controller.cpp src/renderer.cpp src/snake.cpp src/roadblock_node.cpp)
target_include_directories(SnakeGame PRIVATE ${PROJECT_SOURCE_DIR}/SDL2 include/)

if (WIN32)
    target_link_libraries(SnakeGame mingw32 SDL2main SDL2-static)
else()
    target_link_libraries(SnakeGame SDL2main SDL2-static)
endif()