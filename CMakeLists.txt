cmake_minimum_required(VERSION 2.8) 

set(PLATFORM "linux" CACHE STRING "Platform to compile")
set(CMAKE_CXX_FLAGS "-Wall -std=c++11 -Wno-unknown-pragmas -DMVCGAME_PLATFORM_LINUX")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(mvcgame)

# rapidxml
include_directories(lib/rapidxml)

# spine
include_directories(lib/spine/include)
set(SPINE_SOURCE_DIR "lib/spine/src/spine")
file(GLOB SPINE_SOURCES
	"${SPINE_SOURCE_DIR}/*.c"
)
add_library(spine ${SPINE_SOURCES})

# library
include_directories(src)
include_directories(lib)
set(MVCGAME_SOURCE_DIR "src/mvcgame")

file(GLOB MVCGAME_SOURCES
	"${MVCGAME_SOURCE_DIR}/*.cpp"
	"${MVCGAME_SOURCE_DIR}/base/*.cpp"
	"${MVCGAME_SOURCE_DIR}/action/*.cpp"
	"${MVCGAME_SOURCE_DIR}/controller/*.cpp"
	"${MVCGAME_SOURCE_DIR}/event/*.cpp"
	"${MVCGAME_SOURCE_DIR}/model/*.cpp"
	"${MVCGAME_SOURCE_DIR}/font/*.cpp"
	"${MVCGAME_SOURCE_DIR}/tile/*.cpp"	
	"${MVCGAME_SOURCE_DIR}/texture/*.cpp"
	"${MVCGAME_SOURCE_DIR}/skeleton/*.cpp"	
	"${MVCGAME_SOURCE_DIR}/asset/*.cpp"
	"${MVCGAME_SOURCE_DIR}/view/*.cpp"
	"${MVCGAME_SOURCE_DIR}/platform/*.cpp"
	"${MVCGAME_SOURCE_DIR}/util/*.cpp"
)

# examples
include_directories(examples)

# examples: hello
set(MVCGAME_EXAMPLE_HELLO_SOURCE_DIR "examples/hello")
file(GLOB MVCGAME_EXAMPLE_HELLO_SOURCES
	"${MVCGAME_EXAMPLE_HELLO_SOURCE_DIR}/*.cpp"
	"${MVCGAME_EXAMPLE_HELLO_SOURCE_DIR}/base/*.cpp"
	"${MVCGAME_EXAMPLE_HELLO_SOURCE_DIR}/asset/*.cpp"	
	"${MVCGAME_EXAMPLE_HELLO_SOURCE_DIR}/action/*.cpp"
	"${MVCGAME_EXAMPLE_HELLO_SOURCE_DIR}/controller/*.cpp"
	"${MVCGAME_EXAMPLE_HELLO_SOURCE_DIR}/event/*.cpp"
	"${MVCGAME_EXAMPLE_HELLO_SOURCE_DIR}/model/*.cpp"
	"${MVCGAME_EXAMPLE_HELLO_SOURCE_DIR}/texture/*.cpp"
	"${MVCGAME_EXAMPLE_HELLO_SOURCE_DIR}/view/*.cpp"
)

# examples: tiled
set(MVCGAME_EXAMPLE_TILED_SOURCE_DIR "examples/tiled")
file(GLOB MVCGAME_EXAMPLE_TILED_SOURCES
	"${MVCGAME_EXAMPLE_TILED_SOURCE_DIR}/*.cpp"
	"${MVCGAME_EXAMPLE_TILED_SOURCE_DIR}/base/*.cpp"
	"${MVCGAME_EXAMPLE_TILED_SOURCE_DIR}/asset/*.cpp"	
	"${MVCGAME_EXAMPLE_TILED_SOURCE_DIR}/action/*.cpp"
	"${MVCGAME_EXAMPLE_TILED_SOURCE_DIR}/controller/*.cpp"
	"${MVCGAME_EXAMPLE_TILED_SOURCE_DIR}/event/*.cpp"
	"${MVCGAME_EXAMPLE_TILED_SOURCE_DIR}/model/*.cpp"
	"${MVCGAME_EXAMPLE_TILED_SOURCE_DIR}/texture/*.cpp"
	"${MVCGAME_EXAMPLE_TILED_SOURCE_DIR}/view/*.cpp"
)

# linux
if("${PLATFORM}" STREQUAL "linux")
	set(MVCGAME_EXAMPLE_HELLO_PLATFORM_SOURCES "${MVCGAME_EXAMPLE_HELLO_SOURCE_DIR}/platform/linux/main.cpp")
	set(MVCGAME_EXAMPLE_TILED_PLATFORM_SOURCES "${MVCGAME_EXAMPLE_TILED_SOURCE_DIR}/platform/linux/main.cpp")
	file(GLOB MVCGAME_PLATFORM_SOURCES
		"${MVCGAME_SOURCE_DIR}/platform/gl/*.cpp"
		"${MVCGAME_SOURCE_DIR}/platform/linux/*.cpp"
	)
	set(MVCGAME_EXAMPLE_COMPILE_FLAGS "-lX11 -lGL -lGLU -lpng -lz")
endif()

add_library(mvcgame ${MVCGAME_SOURCES} ${MVCGAME_PLATFORM_SOURCES})

add_executable(hello ${MVCGAME_EXAMPLE_HELLO_SOURCES} ${MVCGAME_EXAMPLE_HELLO_PLATFORM_SOURCES})
target_link_libraries(hello mvcgame ${MVCGAME_EXAMPLE_COMPILE_FLAGS})
target_link_libraries(hello spine)

add_executable(tiled ${MVCGAME_EXAMPLE_TILED_SOURCES} ${MVCGAME_EXAMPLE_TILED_PLATFORM_SOURCES})
target_link_libraries(tiled mvcgame ${MVCGAME_EXAMPLE_COMPILE_FLAGS})

# unit tests
add_subdirectory(lib/googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
aux_source_directory(test MVCGAME_TESTS)
add_executable(runUnitTests ${MVCGAME_TESTS})
target_link_libraries(runUnitTests mvcgame gtest gtest_main z)
add_test(runUnitTests runUnitTests)
