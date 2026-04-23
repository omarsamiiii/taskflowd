cmake_minimum_required(VERSION 3.16)

project(taskflowd VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(taskflowd_lib
    src/workflow.cpp
)

target_include_directories(taskflowd_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(taskflowd
    src/main.cpp
)

target_link_libraries(taskflowd
    PRIVATE
        taskflowd_lib
)

enable_testing()

add_executable(test_workflow
    tests/test_workflow.cpp
)

target_link_libraries(test_workflow
    PRIVATE
        taskflowd_lib
)

add_test(NAME workflow_tests COMMAND test_workflow)