cmake_minimum_required(VERSION 2.8)
project(KoRE)



if(MSVC10)	
    message("Compiler is MSVC.")    
endif()
if(CMAKE_COMPILER_IS_GNUCXX)
    message("Compiler is GNU++")
endif()

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

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-std=c++0x") 
    #SET(CMAKE_EXE_LINKER_FLAGS "-static-libgcc")
    SET(CMAKE_EXE_LINKER_FLAGS "-static-libstdc++")
endif()

# Build KoRE library
file(GLOB_RECURSE SOURCES src/KoRE/*.cpp)
file(GLOB_RECURSE HEADER src/KoRE/*.h)
add_library(KoRE ${SOURCES} ${HEADER})
include_directories(src)

# Build Clipper library (?!)
#file(GLOB_RECURSE SOURCES ext/contrib/clipper/*.cpp)
#file(GLOB_RECURSE HEADER ext/contrib/clipper/*.hpp)
#add_library(clipper ${SOURCES} ${HEADER})

# Build Tinyxml library (?!)
#file(GLOB_RECURSE SOURCES ext/include/tinyxml/*.cpp)
#file(GLOB_RECURSE HEADER ext/include/tinyxml/*.h)
#add_library(tinyxml ${SOURCES} ${HEADER})
#include_directories( ext/include/tinyxml)

# Build poly2Tri library (?!)
#file(GLOB_RECURSE SOURCES ext/contrib/poly2tri/poly2tri/*.cpp)
#file(GLOB_RECURSE HEADER ext/contrib/poly2tri/poly2tri/*.h)
#add_library(p2t ${SOURCES} ${HEADER})
#SET_TARGET_PROPERTIES(p2t PROPERTIES LINKER_LANGUAGE C)


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
		set_target_properties( assimp PROPERTIES IMPORTED_LOCATION ${CMAKE_LIBRARY_PATH}/libassimp.a )

		target_link_libraries(KoRE opengl32)
	else()
		#Linux
		add_definitions(-DGLEW_STATIC)
		target_link_libraries(KoRE GLEW)	
	endif(WIN32)
	
	target_link_libraries(KoRE tinyxml)		
	target_link_libraries(KoRE assimp) 	
endif() 

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
