# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/model_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/model_autogen.dir/ParseCache.txt"
  "model_autogen"
  )
endif()
