# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/a14_georgerapeanu_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/a14_georgerapeanu_autogen.dir/ParseCache.txt"
  "a14_georgerapeanu_autogen"
  )
endif()
