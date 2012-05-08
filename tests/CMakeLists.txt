message(STATUS "Building Tests")

add_executable(simpleTest simpleTest.cpp ../include/einhard/einhard.hpp)
add_test(Simple simpleTest)

add_executable(simpleTest_NDEBUG simpleTest.cpp)
add_target_property(simpleTest_NDEBUG COMPILE_FLAGS "-DNDEBUG")
add_test(Simple2 simpleTest_NDEBUG)

add_executable(multipleSources source1.cpp source2.cpp)
add_test(MultipleSource multipleSources)

set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost 1.35.0 COMPONENTS thread)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(threaded threaded.cpp)
target_link_libraries(threaded ${Boost_LIBRARIES})
add_test(Threaded threaded)
