# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/practical_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/practical_autogen.dir/ParseCache.txt"
  "practical_autogen"
  )
endif()
