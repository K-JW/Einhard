message(STATUS "Building Tests")

add_executable(simpleTest simpleTest.cpp)
add_test(Simple simpleTest)

