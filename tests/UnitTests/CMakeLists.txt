enable_testing()

file(GLOB_RECURSE SOURCES *.cpp)
add_executable(UnitTests ${SOURCES})

target_link_libraries(UnitTests PUBLIC Tasks::Shared GTest::gtest_main)
add_test(NAME UnitTests
         COMMAND UnitTests)

include(GoogleTest)
gtest_discover_tests(UnitTests)