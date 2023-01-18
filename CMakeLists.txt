cmake_minimum_required(VERSION 3.25)
project(ray_tracer_challenge)
include(FetchContent)
enable_testing()

set(CMAKE_CXX_STANDARD 20)

FetchContent_Declare(
        yaml-cpp
        GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
        GIT_TAG yaml-cpp-0.7.0
)
FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 0.9.9.8
)
FetchContent_Declare(
        SDL2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-2.26.2
)
FetchContent_Declare(
        GTest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.13.0
)
FetchContent_MakeAvailable(yaml-cpp glm SDL2 GTest)

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
        glm
        yaml-cpp
)

add_executable(ray_tracer_challange_tests ${TESTS} ${TEST_SOURCES})
target_link_libraries(
        ray_tracer_challange_tests
        GTest::gtest_main
        SDL2
        glm
        yaml-cpp
)

include(GoogleTest)
gtest_discover_tests(ray_tracer_challange_tests)

if (UNIX)
    add_compile_options(-Wall -Wextra -pedantic)
endif ()