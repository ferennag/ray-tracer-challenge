cmake_minimum_required(VERSION 3.25)
project(ray_tracer_challenge)
enable_testing()

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)
find_package(glm REQUIRED)
find_package(GTest REQUIRED)

file(GLOB_RECURSE SOURCES
        src/*.h
        src/*.cpp)

file(GLOB_RECURSE TEST_SOURCES
        src/*.h
        src/*.cpp)

list(FILTER TEST_SOURCES EXCLUDE REGEX "main.cpp")

file(GLOB_RECURSE TESTS
        test/*.h
        test/*.cpp)

add_executable(ray_tracer_challenge ${SOURCES})
target_link_libraries(ray_tracer_challenge
        SDL2
        glm)

add_executable(ray_tracer_challange_tests ${TESTS} ${TEST_SOURCES})
target_link_libraries(
        ray_tracer_challange_tests
        GTest::gtest_main
        SDL2
        glm
)

include(GoogleTest)
gtest_discover_tests(ray_tracer_challange_tests)

if(UNIX)
    add_compile_options(-Wall -Wextra -pedantic)
endif()