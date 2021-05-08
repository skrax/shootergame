cmake_minimum_required(VERSION 3.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Shooter VERSION 0.1)

find_package(SDL2 CONFIG REQUIRED)

string(TIMESTAMP time "%Y%M%d%H%M%S")
file(WRITE .ts_comp ${time})

add_executable(Shooter main.cc)
target_link_libraries(Shooter PRIVATE SDL2::SDL2)
target_compile_features(Shooter PRIVATE cxx_std_20)
