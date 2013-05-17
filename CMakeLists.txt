cmake_minimum_required(VERSION 2.8) 

set(PLATFORM "linux" CACHE STRING "Platform to compile")
set(CMAKE_CXX_FLAGS "-Wall -std=c++11 -Wno-unknown-pragmas -DMVCGAME_PLATFORM_COCOS2DX")
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )

set(COCOS2D_FIX_COMPILE_FLAGS "-Wno-unused-variable -Wno-unused-function -Wno-sign-compare -Wno-conversion-null -Wno-unused-but-set-variable -Wno-reorder")

project(mvcgame)

# library
include_directories(src)
set(MVCGAME_SOURCE_DIR "src/mvcgame")
file(GLOB MVCGAME_SOURCES
	"${MVCGAME_SOURCE_DIR}/*.cpp"
	"${MVCGAME_SOURCE_DIR}/action/*.cpp"
	"${MVCGAME_SOURCE_DIR}/controller/*.cpp"
	"${MVCGAME_SOURCE_DIR}/event/*.cpp"
	"${MVCGAME_SOURCE_DIR}/model/*.cpp"
	"${MVCGAME_SOURCE_DIR}/texture/*.cpp"
	"${MVCGAME_SOURCE_DIR}/view/*.cpp"
) 
add_library(mvcgame ${MVCGAME_SOURCES} ${MVCGAME_PLATFORM_SOURCES})
set_target_properties(mvcgame PROPERTIES COMPILE_FLAGS "${LIBRARY_COMPILE_FLAGS}")

# examples
include_directories(examples)

# examples: hello
set(MVCGAME_EXAMPLE_HELLO_SOURCE_DIR "examples/hello")
file(GLOB MVCGAME_EXAMPLE_HELLO_SOURCES
	"${MVCGAME_EXAMPLE_HELLO_SOURCE_DIR}/*.cpp"
	"${MVCGAME_EXAMPLE_HELLO_SOURCE_DIR}/action/*.cpp"
	"${MVCGAME_EXAMPLE_HELLO_SOURCE_DIR}/controller/*.cpp"
	"${MVCGAME_EXAMPLE_HELLO_SOURCE_DIR}/event/*.cpp"
	"${MVCGAME_EXAMPLE_HELLO_SOURCE_DIR}/model/*.cpp"
	"${MVCGAME_EXAMPLE_HELLO_SOURCE_DIR}/texture/*.cpp"
	"${MVCGAME_EXAMPLE_HELLO_SOURCE_DIR}/view/*.cpp"
) 
if("${PLATFORM}" STREQUAL "linux")
	set(MVCGAME_EXAMPLE_HELLO_PLATFORM_SOURCES "${MVCGAME_EXAMPLE_HELLO_SOURCE_DIR}/platform/linux/main.cpp")
endif()

add_executable(hello ${MVCGAME_EXAMPLE_HELLO_SOURCES} ${MVCGAME_EXAMPLE_HELLO_PLATFORM_SOURCES})
target_link_libraries(hello mvcgame)

# unit tests
add_subdirectory(lib/googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
aux_source_directory(test MVCGAME_TESTS)
add_executable(runUnitTests ${MVCGAME_TESTS})
target_link_libraries(runUnitTests mvcgame gtest gtest_main)
add_test(runUnitTests runUnitTests)
