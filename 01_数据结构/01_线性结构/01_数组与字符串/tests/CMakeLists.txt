cmake_minimum_required(VERSION 3.10)
project(tests.bin)

add_executable(${PROJECT_NAME} test_vector.cpp test_vectorPlus.cpp)
target_link_libraries(${PROJECT_NAME} GTest::gtest GTest::gtest_main)