file(GLOB_RECURSE SOURCES *.cpp)

add_executable(MainGLFW ${SOURCES})

#if(MSVC)
if(WIN32)
<<<<<<< HEAD
  link_directories(${CMAKE_SOURCE_DIR}/ext/lib/)
	target_link_libraries(MainGLFW 
	  GLFW.lib 
	  KoRE 
	  glew32.lib 
	  assimp32.lib
=======
	target_link_libraries(
      MainGLFW 
	  OpenGL32.lib 
	  ${CMAKE_SOURCE_DIR}/ext/lib/GLFW.lib 
	  ${CMAKE_SOURCE_DIR}/lib/$(Configuration)/KoRE.lib 
	  ${CMAKE_SOURCE_DIR}/ext/lib/glew32.lib 
	  ${CMAKE_SOURCE_DIR}/ext/lib/assimp32.lib 
>>>>>>> 17b0ded909c84cc2461c25ff2016d800a4b19e44
	  )
else()
  target_link_libraries(MainGLFW glfw GL GLEW KoRE assimp)
endif()


