cmake_minimum_required(VERSION 3.16)
project(ray_tracing
  VERSION 0.0.1
  LANGUAGES CXX
)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(CMAKE_CXX_FLAGS "-g")

find_package(OpenMP REQUIRED)
find_package(MPI REQUIRED)

add_subdirectory(lib)
add_subdirectory(app)