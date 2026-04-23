cmake_minimum_required(VERSION 3.16)

project(taskflowd VERSION 0.2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(taskflowd_lib
    src/workflow.cpp
    src/validation.cpp
    src/scheduler.cpp
    src/parser.cpp
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

add_executable(test_validation
    tests/test_validation.cpp
)

target_link_libraries(test_validation
    PRIVATE
        taskflowd_lib
)

add_test(NAME validation_tests COMMAND test_validation)

add_executable(test_scheduler
    tests/test_scheduler.cpp
)

target_link_libraries(test_scheduler
    PRIVATE
        taskflowd_lib
)

add_test(NAME scheduler_tests COMMAND test_scheduler)

add_executable(test_parser
    tests/test_parser.cpp
)

target_link_libraries(test_parser
    PRIVATE
        taskflowd_lib
)

add_test(NAME parser_tests COMMAND test_parser)