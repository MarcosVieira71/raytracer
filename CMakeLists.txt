cmake_minimum_required(VERSION 3.15)
project(raytracer LANGUAGES CXX)

find_package(glm REQUIRED)

file(GLOB SOURCES src/*.cpp)
add_executable(raytracer ${SOURCES})

target_link_libraries(raytracer PRIVATE glm::glm)