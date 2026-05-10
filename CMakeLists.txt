cmake_minimum_required(VERSION 3.15...4.0.0)
include(FetchContent)

project(snake_tui LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

# project sources
include_directories(${CMAKE_SOURCE_DIR}/include)
add_executable(snake_tui
  src/main.cpp
  src/Game.cpp
  src/Snake.cpp
)

# ftxui stuff
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI
  GIT_TAG v6.1.9
)
FetchContent_MakeAvailable(ftxui)

target_link_libraries(snake_tui
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
)