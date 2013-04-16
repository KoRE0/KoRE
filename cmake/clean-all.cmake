# delete all cmake-generated files

# cmake folde
FILE(GLOB_RECURSE cmake_generated_folder  
                    CMakeFiles
)

# each folder with CMakeLists has a CMakeFiles folder.
# find these folders

FILE(GLOB_RECURSE cmakelists CMakeLists.txt)
SET(dir_list "")
FOREACH(file_path ${cmakelists})
	GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
	FILE(REMOVE_RECURSE ${dir_path}/CMakeFiles)
ENDFOREACH()


FILE(GLOB_RECURSE cmake_generated_files 	
					CMakeCache.txt
					cmake_install.cmake  
					Makefile
)

foreach(file ${cmake_generated_folder})

  if (EXISTS ${file})
     file(REMOVE_RECURSE ${file})
  endif()

endforeach(file)

foreach(file ${cmake_generated_files})

  if (EXISTS ${file})
     file(REMOVE ${file})
  endif()

endforeach(file)

# find all other generated files (project files ect.)
FILE(GLOB_RECURSE other_files *.sln *.vcxproj *.project *.vcxproj.filters *.cproject)
foreach(file ${other_files})

  if (EXISTS ${file})
     file(REMOVE ${file})
  endif()

endforeach(file)

message( FATAL_ERROR "DELETIONS COMPLETE. This Error message appears because CMake has just deleted its own targets and cannot exit without error.")
