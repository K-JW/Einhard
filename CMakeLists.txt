cmake_minimum_required(VERSION 2.8.0)
project(Einhard)

macro(add_target_property _target _prop _value)
   get_target_property(_oldprop "${_target}" ${_prop})
   if(NOT _oldprop)
      set_target_properties("${_target}" PROPERTIES ${_prop} "${_value}")
   else(NOT _oldprop)
      set_target_properties("${_target}" PROPERTIES ${_prop} "${_oldprop} ${_value}")
   endif(NOT _oldprop)
endmacro(add_target_property)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER MATCHES "/clang\\+\\+$")
	set(CMAKE_CXX_FLAGS           "${CMAKE_CXX_FLAGS} -Wall -Wextra -ansi -pedantic -Wdisabled-optimization")
	set(CMAKE_CXX_FLAGS_RELEASE   "-O3")
	set(CMAKE_CXX_FLAGS_DEBUG     "-g -O0 -fno-reorder-blocks -fno-schedule-insns -fno-inline")
	set(CMAKE_CXX_FLAGS_DEBUGFULL "-g3 -fno-linline")
endif(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER MATCHES "/clang\\+\\+$")
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_CXX_COMPILER MATCHES "/clang$")
	set(CMAKE_C_FLAGS             "${CMAKE_C_FLAGS} -Wall -Wextra -ansi -pedantic -Wc++-compat -Wdisabled-optimization")
	set(CMAKE_C_FLAGS_RELEASE     "-O3")
	set(CMAKE_C_FLAGS_DEBUG       "-g -O0 -fno-reorder-blocks -fno-schedule-insns -fno-inline")
	set(CMAKE_C_FLAGS_DEBUGFULL   "-g3 -fno-linline")
endif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_CXX_COMPILER MATCHES "/clang$")

set(CMAKE_CXX_FLAGS           "${CMAKE_CXX_FLAGS} -std=c++11")

# We have an include directory
include_directories(include/einhard)

add_library(einhard src/einhard.cpp)

# Install the header files
install(DIRECTORY include/einhard DESTINATION include)

# Take care of Test
include (CTest)

if(BUILD_TESTING)
	add_subdirectory(tests)
endif(BUILD_TESTING)

# Documentation
include(FindDoxygen)
if(DOXYGEN_FOUND)
    add_subdirectory(doc)
else(DOXYGEN_FOUND)
    message(STATUS "WARNING: Failed to find Doxygen - won't build documentation")
endif(DOXYGEN_FOUND)

