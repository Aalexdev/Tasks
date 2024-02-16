

file(GLOB_RECURSE SOURCES *.cpp)
add_executable(Testbed ${SOURCES})

target_link_libraries(Testbed PUBLIC Tasks::Shared)


set_target_properties(Testbed PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")