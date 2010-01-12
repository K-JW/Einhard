message(STATUS "Building Tests")

add_executable(simpleTest simpleTest.cpp)
add_test(Simple simpleTest)

add_executable(simpleTest_NDEBUG simpleTest.cpp)
add_target_property(simpleTest_NDEBUG COMPILE_FLAGS "-DNDEBUG")
add_test(Simple2 simpleTest_NDEBUG)
