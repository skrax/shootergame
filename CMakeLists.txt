cmake_minimum_required(VERSION 3.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Shooter VERSION 0.1)

find_package(SDL2 CONFIG REQUIRED)

add_executable(ShooterMain main.cc)
target_link_libraries(ShooterMain PRIVATE SDL2::SDL2)
target_compile_features(ShooterMain PRIVATE cxx_std_20)

add_library(Shooter SHARED shooter.cc)
target_link_libraries(Shooter PRIVATE SDL2::SDL2)
target_compile_features(ShooterMain PRIVATE cxx_std_20)

add_custom_command(TARGET Shooter POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -P "${CMAKE_CURRENT_SOURCE_DIR}/cmake/compilation_timestamp.cmake")
