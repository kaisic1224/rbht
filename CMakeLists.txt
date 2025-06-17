cmake_minimum_required(VERSION 3.14)
project(tetris)

# GoogleTest requires at least C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -g "-fsanitize=address,undefined")
add_link_options("-fsanitize=address,undefined")

find_package(SDL2 REQUIRED)

include_directories(src ${SDL2_INCLUDE_DIRS})

add_executable(tetris
    src/main.cpp
    src/board.cpp
    src/block.cpp
    src/blockbag.cpp
)

target_link_libraries(tetris ${SDL2_LIBRARIES})

# include(FetchContent)
# FetchContent_Declare(
#   googletest
#   URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
# )
#
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# FetchContent_MakeAvailable(googletest)
#
# enable_testing()
#
# add_executable(
#     test_block
#     tests/test_block.cpp
# )
# target_link_libraries(
#   test_block
#   GTest::gtest_main
# )
#
# include(GoogleTest)
# gtest_discover_tests(test_block)
