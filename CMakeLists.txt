cmake_minimum_required(VERSION 3.22.1)
project(Tasks VERSION 0.1.0)

# Set C++ standard and build type
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(TASKS_SHARED_LIBRARY "Build the shared library" ON)
option(TASKS_STATIC_LIBRARY "Build the static library" ON)
option(TASKS_TESTS "Build the tests executable" OFF)
option(TASKS_EXAMPLES "Build the examples executables" OFF)

file(GLOB_RECURSE SOURCES src/*.cpp)

set(PROJECT_BINARY_DIR "${PROJECT_BINARY_DIR}/bin")

add_library(Tasks-Shared SHARED ${SOURCES})
add_library(Tasks::Shared ALIAS Tasks-Shared)

set_target_properties(Tasks-Shared
	PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
	LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_include_directories(Tasks-Shared PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/includes/")

add_subdirectory(tests)