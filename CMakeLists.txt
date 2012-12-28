cmake_minimum_required(VERSION 2.8) 

set(PLATFORM "linux" CACHE STRING "Platform to compile")
set(LIBRARY "cocos2dx" CACHE STRING "library to compile")
set(CMAKE_CXX_FLAGS "-Wall -std=c++11 -Wno-unknown-pragmas -DMVCGAME_PLATFORM_COCOS2DX")
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )

set(COCOS2D_FIX_COMPILE_FLAGS "-Wno-unused-variable -Wno-unused-function -Wno-sign-compare -Wno-conversion-null -Wno-unused-but-set-variable -Wno-reorder")

project(mvcgame)

# cocos2dx
if("${LIBRARY}" STREQUAL "cocos2dx")
	set(COCOS2DX_SOURCE_DIR "${PROJECT_SOURCE_DIR}/lib/cocos2d-x/cocos2dx")
	include_directories(${COCOS2DX_SOURCE_DIR}/..)
	include_directories(${COCOS2DX_SOURCE_DIR})
	include_directories(${COCOS2DX_SOURCE_DIR}/include)
	include_directories(${COCOS2DX_SOURCE_DIR}/kazmath/include)
	file(GLOB COCOS2DX_SOURCES 
		"${COCOS2DX_SOURCE_DIR}/*.c*" 
		"${COCOS2DX_SOURCE_DIR}/actions/*.c*"
		"${COCOS2DX_SOURCE_DIR}/base_nodes/*.c*"		
		"${COCOS2DX_SOURCE_DIR}/cocoa/*.c*"
		"${COCOS2DX_SOURCE_DIR}/effects/*.c*"
		"${COCOS2DX_SOURCE_DIR}/extensions/CCBReader/*.c*"
		"${COCOS2DX_SOURCE_DIR}/extensions/CCControlExtension/*.c*"
		"${COCOS2DX_SOURCE_DIR}/extensions/CCListView/*.c*"
		"${COCOS2DX_SOURCE_DIR}/extensions/CCNotificationCenter/*.c*"
		"${COCOS2DX_SOURCE_DIR}/extensions/CCScrollView/*.c*"
		"${COCOS2DX_SOURCE_DIR}/extensions/CCTextureWatcher/*.c*"
		"${COCOS2DX_SOURCE_DIR}/kazmath/src/*.c*"
		"${COCOS2DX_SOURCE_DIR}/kazmath/src/GL/*.c*"
		"${COCOS2DX_SOURCE_DIR}/keypad_dispatcher/*.c*"
		"${COCOS2DX_SOURCE_DIR}/label_nodes/*.c*"
		"${COCOS2DX_SOURCE_DIR}/layers_scenes_transitions_nodes/*.c*"
		"${COCOS2DX_SOURCE_DIR}/menu_nodes/*.c*"
		"${COCOS2DX_SOURCE_DIR}/misc_nodes/*.c*"
		"${COCOS2DX_SOURCE_DIR}/particle_nodes/*.c*"
		"${COCOS2DX_SOURCE_DIR}/platform/*.c*"
		"${COCOS2DX_SOURCE_DIR}/script_support/*.c*"
		"${COCOS2DX_SOURCE_DIR}/shaders/*.c*"
		"${COCOS2DX_SOURCE_DIR}/sprite_nodes/*.c*"
		"${COCOS2DX_SOURCE_DIR}/support/*.c*"
		"${COCOS2DX_SOURCE_DIR}/support/data_support/*.c*"
		"${COCOS2DX_SOURCE_DIR}/support/image_support/*.c*"
		"${COCOS2DX_SOURCE_DIR}/support/zip_support/*.c*" #?todo
		"${COCOS2DX_SOURCE_DIR}/text_input_node/*.c*"
		"${COCOS2DX_SOURCE_DIR}/textures/*.c*"
		"${COCOS2DX_SOURCE_DIR}/tileMap_parallax_nodes/*.c*"
		"${COCOS2DX_SOURCE_DIR}/touch_dispatcher/*.c*"
	)
	file(GLOB_RECURSE COCOS2DX_API
		"${COCOS2DX_SOURCE_DIR}/*.c*" 
		"${COCOS2DX_SOURCE_DIR}/actions/*.c*"
		"${COCOS2DX_SOURCE_DIR}/base_nodes/*.c*"		
		"${COCOS2DX_SOURCE_DIR}/cocoa/*.c*"
		"${COCOS2DX_SOURCE_DIR}/effects/*.c*"
		"${COCOS2DX_SOURCE_DIR}/extensions/CCBReader/*.c*"
		"${COCOS2DX_SOURCE_DIR}/extensions/CCControlExtension/*.c*"
		"${COCOS2DX_SOURCE_DIR}/extensions/CCListView/*.c*"
		"${COCOS2DX_SOURCE_DIR}/extensions/CCNotificationCenter/*.c*"
		"${COCOS2DX_SOURCE_DIR}/extensions/CCScrollView/*.c*"
		"${COCOS2DX_SOURCE_DIR}/extensions/CCTextureWatcher/*.c*"
		"${COCOS2DX_SOURCE_DIR}/kazmath/src/*.c*"
		"${COCOS2DX_SOURCE_DIR}/kazmath/src/GL/*.c*"
		"${COCOS2DX_SOURCE_DIR}/keypad_dispatcher/*.c*"
		"${COCOS2DX_SOURCE_DIR}/label_nodes/*.c*"
		"${COCOS2DX_SOURCE_DIR}/layers_scenes_transitions_nodes/*.c*"
		"${COCOS2DX_SOURCE_DIR}/menu_nodes/*.c*"
		"${COCOS2DX_SOURCE_DIR}/misc_nodes/*.c*"
		"${COCOS2DX_SOURCE_DIR}/particle_nodes/*.c*"
		"${COCOS2DX_SOURCE_DIR}/platform/*.c*"
		"${COCOS2DX_SOURCE_DIR}/script_support/*.c*"
		"${COCOS2DX_SOURCE_DIR}/shaders/*.c*"
		"${COCOS2DX_SOURCE_DIR}/sprite_nodes/*.c*"
		"${COCOS2DX_SOURCE_DIR}/support/*.c*"
		"${COCOS2DX_SOURCE_DIR}/support/data_support/*.c*"
		"${COCOS2DX_SOURCE_DIR}/support/image_support/*.c*"
		"${COCOS2DX_SOURCE_DIR}/support/zip_support/*.c*" #?todo
		"${COCOS2DX_SOURCE_DIR}/text_input_node/*.c*"
		"${COCOS2DX_SOURCE_DIR}/textures/*.c*"
		"${COCOS2DX_SOURCE_DIR}/tileMap_parallax_nodes/*.c*"
		"${COCOS2DX_SOURCE_DIR}/touch_dispatcher/*.c*"
	)
	if("${PLATFORM}" STREQUAL "linux")
		find_package(OpenGL REQUIRED)
		include(FindPkgConfig)
		set(COCOS2DX_PLATFORM_DIR "${COCOS2DX_SOURCE_DIR}/platform/linux")
		set(COCOS2DX_PLATFORM_THIRDPARTY_DIR "${COCOS2DX_SOURCE_DIR}/platform/third_party/linux")		
		if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
			set(COCOS2DX_PLATFORM_LIBRARIES_DIR "${COCOS2DX_PLATFORM_THIRDPARTY_DIR}/libraries/lib64")
		else( CMAKE_SIZEOF_VOID_P EQUAL 4 )
			set(COCOS2DX_PLATFORM_LIBRARIES_DIR "${COCOS2DX_PLATFORM_THIRDPARTY_DIR}/libraries")
		endif()
		file(GLOB COCOS2DX_PLATFORM_SOURCES
			"${COCOS2DX_PLATFORM_DIR}/*.c*"
		)
		include_directories("${COCOS2DX_PLATFORM_DIR}"
			"${COCOS2DX_PLATFORM_THIRDPARTY_DIR}/glew-1.7.0/glew-1.7.0/include"
			"${COCOS2DX_PLATFORM_THIRDPARTY_DIR}/libxml2"
			"${COCOS2DX_PLATFORM_THIRDPARTY_DIR}/libpng"
			"${COCOS2DX_PLATFORM_THIRDPARTY_DIR}/libjpeg"
			"${COCOS2DX_PLATFORM_THIRDPARTY_DIR}/libfreetype2"
			"${COCOS2DX_PLATFORM_THIRDPARTY_DIR}/libtiff/include"
			"${OPENGL_INCLUDE_DIR}"
		)
		set(COCOS2D_COMPILE_FLAGS "-DLINUX")
		link_directories("${COCOS2DX_PLATFORM_LIBRARIES_DIR}")
		set(COCOS2D_LIBRARIES ${OPENGL_LIBRARIES} GLEW glfw freetype fontconfig xml2 png jpeg tiff z)	
	else()
		message(FATAL_ERROR "Invalid platform '${PLATFORM}'.")
	endif()

	add_library(cocos2dx ${COCOS2DX_SOURCES} ${COCOS2DX_PLATFORM_SOURCES})
	set_target_properties(cocos2dx PROPERTIES COMPILE_FLAGS "${COCOS2D_FIX_COMPILE_FLAGS} ${COCOS2D_COMPILE_FLAGS}")
	target_link_libraries(cocos2dx ${COCOS2D_LIBRARIES})
enDif()

# library
include_directories(src)
aux_source_directory(src/mvcgame MVCGAME_SOURCES)
if("${LIBRARY}" STREQUAL "cocos2dx")
	aux_source_directory(src/mvcgame/platform/cocos2dx MVCGAME_PLATFORM_SOURCES)
	set(LIBRARY_COMPILE_FLAGS "-DLINUX")
endif()
add_library(mvcgame ${MVCGAME_SOURCES} ${MVCGAME_PLATFORM_SOURCES})
set_target_properties(mvcgame PROPERTIES COMPILE_FLAGS "${LIBRARY_COMPILE_FLAGS}")
target_link_libraries(mvcgame cocos2dx)

# examples
include_directories(examples)

# examples: hello
if("${PLATFORM}" STREQUAL "linux")
	add_executable(hello examples/hello/platform/linux/main.cpp)
endif()

target_link_libraries(hello mvcgame)

# unit tests
add_subdirectory(lib/googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
aux_source_directory(test MVCGAME_TESTS)
add_executable(runUnitTests ${MVCGAME_TESTS})
target_link_libraries(runUnitTests mvcgame gtest gtest_main)
add_test(runUnitTests runUnitTests)
