message(STATUS "Building Tests")

add_executable(simpleTest simpleTest.cpp ../include/einhard/einhard.hpp)
target_link_libraries(simpleTest einhard)
add_test(Simple simpleTest)

add_executable(simpleTest_NDEBUG simpleTest.cpp)
target_link_libraries(simpleTest_NDEBUG einhard)
add_target_property(simpleTest_NDEBUG COMPILE_FLAGS "-DNDEBUG")
add_test(Simple2 simpleTest_NDEBUG)

add_executable(multipleSources source1.cpp source2.cpp)
target_link_libraries(multipleSources einhard)
add_test(MultipleSource multipleSources)

add_executable(threaded threaded.cpp)
target_link_libraries(threaded einhard)
set_target_properties(threaded PROPERTIES COMPILE_FLAGS "-pthread" LINK_FLAGS "-pthread")
add_test(Threaded threaded)
