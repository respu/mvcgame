cmake_minimum_required(VERSION 2.8) 

set(PLATFORM "linux" CACHE STRING "Platform to compile")
set(CMAKE_CXX_FLAGS "-Wall -std=c++11 -Wno-unknown-pragmas -DMVCGAME_PLATFORM_LINUX")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DMVCGAME_DEBUG_DRAW -DMVCGAME_DEBUG_TEXTURE_PNG")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(mvcgame)

# library
include_directories(src)
set(MVCGAME_SOURCE_DIR "src/mvcgame")

file(GLOB MVCGAME_SOURCES
	"${MVCGAME_SOURCE_DIR}/*.cpp"
	"${MVCGAME_SOURCE_DIR}/base/*.cpp"
	"${MVCGAME_SOURCE_DIR}/action/*.cpp"
	"${MVCGAME_SOURCE_DIR}/controller/*.cpp"
	"${MVCGAME_SOURCE_DIR}/event/*.cpp"
	"${MVCGAME_SOURCE_DIR}/model/*.cpp"
	"${MVCGAME_SOURCE_DIR}/texture/*.cpp"
	"${MVCGAME_SOURCE_DIR}/view/*.cpp"
	"${MVCGAME_SOURCE_DIR}/platform/*.cpp"	
)

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

# linux
if("${PLATFORM}" STREQUAL "linux")
	set(MVCGAME_EXAMPLE_HELLO_PLATFORM_SOURCES "${MVCGAME_EXAMPLE_HELLO_SOURCE_DIR}/platform/linux/main.cpp")
	file(GLOB MVCGAME_PLATFORM_SOURCES
		"${MVCGAME_SOURCE_DIR}/platform/gl/*.cpp"
		"${MVCGAME_SOURCE_DIR}/platform/linux/*.cpp"
	)
	set(MVCGAME_EXAMPLE_COMPILE_FLAGS "-lX11 -lGL -lGLU -lpng")
endif()

add_library(mvcgame ${MVCGAME_SOURCES} ${MVCGAME_PLATFORM_SOURCES})

add_executable(hello ${MVCGAME_EXAMPLE_HELLO_SOURCES} ${MVCGAME_EXAMPLE_HELLO_PLATFORM_SOURCES})
target_link_libraries(hello mvcgame ${MVCGAME_EXAMPLE_COMPILE_FLAGS})

# unit tests
add_subdirectory(lib/googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
aux_source_directory(test MVCGAME_TESTS)
add_executable(runUnitTests ${MVCGAME_TESTS})
target_link_libraries(runUnitTests mvcgame gtest gtest_main)
add_test(runUnitTests runUnitTests)
