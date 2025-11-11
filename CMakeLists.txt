cmake_minimum_required(VERSION 3.15)
project(raytracer LANGUAGES CXX)
set(CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}" ${CMAKE_PREFIX_PATH})

find_package(glm REQUIRED)
find_package(stb REQUIRED)
find_package(SDL3 CONFIG REQUIRED)
find_package(OpenMP REQUIRED)

file(GLOB SOURCES src/*.cpp)
add_executable(raytracer ${SOURCES})

target_include_directories(raytracer
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(raytracer PRIVATE glm::glm stb::stb SDL3::SDL3 OpenMP::OpenMP_CXX)
