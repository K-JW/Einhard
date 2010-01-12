cmake_minimum_required(VERSION 2.6.2)
project(Einhard)

# Install the header files
install(DIRECTORY include/einhard DESTINATION include)

# Take care of Test
#include (CTest)
#
#if(BUILD_TESTING)
#	add_subdirectory(tests)
#endif(BUILD_TESTING)

