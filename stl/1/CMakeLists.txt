cmake_minimum_required(VERSION 3.22.1)

# === Project ===
project(
  Lab1Vector
  VERSION 1.0
  LANGUAGES CXX)

# === Options ===
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# === Dependencies ===
include(FetchContent)

FetchContent_Declare(
  nanobench
  GIT_REPOSITORY https://github.com/martinus/nanobench.git
  GIT_TAG v4.3.11
  GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(nanobench)

FetchContent_Declare(
  cxxopts
  GIT_REPOSITORY https://github.com/jarro2783/cxxopts.git
  GIT_TAG v3.1.1
  GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(cxxopts)

# === Build ===
add_executable(${PROJECT_NAME} vector.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE nanobench cxxopts)
