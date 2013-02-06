file(GLOB_RECURSE SOURCES *.cpp)
file(GLOB_RECURSE HEADER *.h)


set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(MainQT5 ${SOURCES} ${HEADER})
find_package(Qt5Core)
qt5_use_modules(MainQT5 Core Gui OpenGL Widgets)
if(WIN32)
  set(EXT_LIBS ${CMAKE_SOURCE_DIR}/ext/lib)
  if(MSVC)
    link_directories(${EXT_LIBS})
    set(KoRE_LIBS
        KoRE
        OpenGL32.lib
        #${CMAKE_SOURCE_DIR}/lib/$(Configuration)/KoRE.lib
        ${EXT_LIBS}/glew32.lib
        ${EXT_LIBS}/assimp_debug-dll_win32/assimp.lib
      )
    else()
    #MinGW
    set(KoRE_LIBS
        #${EXT_LIBS}/mingw/libglfw.a
        #${EXT_LIBS}/glew32.lib
        #${EXT_LIBS}/assimp_release-dll_win32/assimp.lib
        #OpenGL32
        #glaux
        #glu32
        opengl32
        glfw
        glew32
        KoRE 
        )
  endif(MSVC)
else()
  #Linux
  set(KoRE_LIBS GL GLEW KoRE assimp)
endif(WIN32)

target_link_libraries(MainQT5 ${KoRE_LIBS})

