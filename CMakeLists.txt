cmake_minimum_required(VERSION 2.8)
project(KoRE)

# For custom cmake modules.
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/lib)

include(GetOpenGLHeaders)
add_custom_target(clean-dependencies
   COMMAND ${CMAKE_COMMAND} -P ${CMAKE_MODULE_PATH}/clean-dependencies.cmake
   COMMENT "Deleting all platform specific Kore dependencies"
)
add_custom_target(clean-all
   COMMAND ${CMAKE_COMMAND} -P ${CMAKE_MODULE_PATH}/clean-dependencies.cmake
   COMMAND ${CMAKE_COMMAND} -P ${CMAKE_MODULE_PATH}/clean-all.cmake
   COMMENT "Deleting all cmake generated files and KoRE dependencies"
)



if(NOT EXISTS ${CMAKE_SOURCE_DIR}/ext OR NOT EXISTS ${CMAKE_SOURCE_DIR}/bin)
  message( FATAL_ERROR "No dependencies found. Please extract dependencies according to your build environment.")
endif()

# create library directory
file(MAKE_DIRECTORY lib)

check_gl_headers()

set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_PATH ${CMAKE_SOURCE_DIR}/ext/lib)

if(APPLE)
    INCLUDE_DIRECTORIES(/System/Library/Frameworks)
    find_library(COCOA_LIBRARY Cocoa)
    find_library(IOKit IOKit)
    find_library(OpenGL_LIBRARY OpenGL)
    MARK_AS_ADVANCED(COCOA_LIBRARY
                     OpenGL_LIBRARY)
    set(EXTRA_LIBS ${COCOA_LIBRARY} ${IOKit} ${OpenGL_LIBRARY})
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-std=c++0x") 
    #set(CMAKE_CXX_FLAGS "-std=gnu++11")
    #SET(CMAKE_EXE_LINKER_FLAGS "-static-libgcc")
    SET(CMAKE_EXE_LINKER_FLAGS "-static-libstdc++")
    add_definitions(-DGXX_EXPERIMENTAL_CXX0X)
    #add_definitions(-D__GXX_EXPERIMENTAL_CXX0X__)
endif()

# Build KoRE library
file(GLOB_RECURSE SOURCES src/KoRE/*.cpp)
file(GLOB_RECURSE HEADER src/KoRE/*.h)
add_library(KoRE ${SOURCES} ${HEADER})
include_directories(src)

if(CMAKE_COMPILER_IS_GNUCXX)
	#Link external libraries to KoRE
	link_directories(${CMAKE_LIBRARY_PATH})
	include_directories(${CMAKE_LIBRARY_PATH})
	
	if(WIN32)
		add_library( tinyxml STATIC IMPORTED)        
		set_target_properties( tinyxml PROPERTIES IMPORTED_LOCATION ${CMAKE_LIBRARY_PATH}/libtinyxml.a)
		
		add_library( clipper STATIC IMPORTED)        
		set_target_properties( clipper PROPERTIES IMPORTED_LOCATION ${CMAKE_LIBRARY_PATH}/libclipper.a)
		target_link_libraries(KoRE clipper)
		
		add_library( p2t STATIC IMPORTED)        
		set_target_properties( p2t PROPERTIES IMPORTED_LOCATION ${CMAKE_LIBRARY_PATH}/libp2t.a)
		target_link_libraries(KoRE p2t)
		
		add_library( glew32 STATIC IMPORTED)        
		set_target_properties( glew32 PROPERTIES IMPORTED_LOCATION ${CMAKE_LIBRARY_PATH}/libglew32.dll.a )
		target_link_libraries(KoRE glew32)
		
		add_library( assimp STATIC IMPORTED)        
		set_target_properties( assimp PROPERTIES IMPORTED_LOCATION ${CMAKE_LIBRARY_PATH}/libassimp.dll )

		target_link_libraries(KoRE opengl32)
	else()
		#Linux
		add_definitions(-DGLEW_STATIC)
		target_link_libraries(KoRE GLEW)	
	endif(WIN32)
	
	target_link_libraries(KoRE tinyxml)		
	target_link_libraries(KoRE assimp) 	
endif() 

if(APPLE)
	add_library( tinyxml STATIC IMPORTED )
	set_target_properties ( tinyxml PROPERTIES IMPORTED_LOCATION  $$${CMAKE_LIBRARY_PATH}/tinyxml.a )

	add_library( assimp STATIC IMPORTED )
	set_target_properties ( assimp PROPERTIES IMPORTED_LOCATION $${CMAKE_LIBRARY_PATH}/libassimp.a )

	add_library( glfw STATIC IMPORTED )
	set_target_properties ( glfw PROPERTIES IMPORTED_LOCATION $${CMAKE_LIBRARY_PATH}/libglfw.a )

	add_library( glew STATIC IMPORTED )
	set_target_properties ( glew PROPERTIES IMPORTED_LOCATION $${CMAKE_LIBRARY_PATH}/libGLEW.a )

	add_library( libz SHARED IMPORTED )
	set_target_properties ( libz PROPERTIES IMPORTED_LOCATION /usr/lib/libz.dylib)

	target_link_libraries(KoRE tinyxml)
	target_link_libraries(KoRE assimp)
	target_link_libraries(KoRE glfw)
	target_link_libraries(KoRE glew)
	target_link_libraries(KoRE libz)

	target_link_libraries(KoRE ${EXTRA_LIBS})
endif(APPLE)

set(IGNORE "-build/include")

#check code stlye
if(EXISTS "/usr/bin/python2")
    set(PYTHON_VER "python2")
else()
    set(PYTHON_VER "python")
endif()


if(WIN32)
  include_directories(${CMAKE_SOURCE_DIR}/ext/include)
  add_definitions(-DGLFW_INCLUDE_GL3)
endif()

set(CMAKE_LIBRARY_PATH  ${CMAKE_SOURCE_DIR}/lib)

#if(MSVC)
#  INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/ext/include)
#  message("Hello MSVC")
#endif()

add_custom_target(style
  COMMAND ${PYTHON_VER} scripts/cpplint.py --filter=${IGNORE} ${SOURCES}
)

ADD_SUBDIRECTORY(demos)
