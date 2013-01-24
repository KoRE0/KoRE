file(GLOB_RECURSE SOURCES *.cpp)

add_executable(MainGLFW ${SOURCES})

if(MSVC)
	target_link_libraries(MainGLFW 
	  ext/lib/GLFW.lib 
	  KoRE 
	  ext/lib/glew32.lib 
	  ext/lib/assimp32.lib
	  )
else()
  target_link_libraries(MainGLFW glfw GL GLEW KoRE assimp)
endif()


