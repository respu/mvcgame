cmake_minimum_required(VERSION 2.6) 
set(CMAKE_CXX_FLAGS "-Wall -std=c++11 -Wno-unknown-pragmas")
set(CMAKE_BINARY_DIR "bin")

project(mvcgame)

include_directories(src)
include_directories(lib/cocos2d-x)

# library
aux_source_directory(src/mvcgame MVCGAME_SOURCES)
add_library(mvcgame ${MVCGAME_SOURCES})

# unit tests
add_subdirectory(lib/googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
aux_source_directory(test MVCGAME_TESTS)
add_executable(runUnitTests ${MVCGAME_TESTS})
target_link_libraries(runUnitTests mvcgame gtest gtest_main)
add_test( runUnitTests runUnitTests )
