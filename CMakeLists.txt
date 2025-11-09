cmake_minimum_required(VERSION 3.15)
project(raytracer LANGUAGES CXX)

find_package(glm REQUIRED)

file(GLOB SOURCES src/*.cpp)
add_executable(raytracer ${SOURCES})

target_include_directories(raytracer
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(raytracer PRIVATE glm::glm)