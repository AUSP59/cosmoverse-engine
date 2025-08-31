
if(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/install_manifest.txt")
  message(FATAL_ERROR "Cannot find install_manifest.txt")
endif()
file(READ "${CMAKE_CURRENT_BINARY_DIR}/install_manifest.txt" files)
string(REGEX REPLACE "
" ";" files_list "${files}")
foreach(f ${files_list})
  if(EXISTS "${f}")
    file(REMOVE "${f}")
    message(STATUS "Removed: ${f}")
  endif()
endforeach()
