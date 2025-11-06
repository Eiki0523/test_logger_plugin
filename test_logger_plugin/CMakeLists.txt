cmake_minimum_required(VERSION 3.20)
project(test_logger_plugin LANGUAGES CXX)

add_library(test_logger SHARED src/test_logger.cpp)

target_compile_features(test_logger PRIVATE cxx_std_17)

if (MSVC)
    set_property(TARGET test_logger PROPERTY
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

target_compile_definitions(test_logger PRIVATE
    UNICODE
    _UNICODE
    WIN32_LEAN_AND_MEAN
    NOMINMAX
)

target_include_directories(test_logger PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set_target_properties(test_logger PROPERTIES
    OUTPUT_NAME "test_logger"
    SUFFIX ".aux2"
)

if (MSVC)
    target_compile_options(test_logger PRIVATE /W4 /permissive-)
else()
    target_compile_options(test_logger PRIVATE -Wall -Wextra -Wpedantic)
endif()
