# cmake_minimum_required(VERSION 3.10)
# project(array)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++20 -fPIC -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer")
# set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# target_include_directories(${PROJECT_NAME} PUBLIC
#     ${PROJECT_SOURCE_DIR}/include/
# )
# # 如果是测试目录，添加Google Test
# if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/test")
#     find_package(GTest REQUIRED)
#     add_subdirectory(test)
# endif()
cmake_minimum_required(VERSION 3.10)
project(array)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++20 -fPIC -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
include_directories(${PROJECT_SOURCE_DIR}/include)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests")
    find_package(GTest REQUIRED)
    add_subdirectory(tests)
endif()


