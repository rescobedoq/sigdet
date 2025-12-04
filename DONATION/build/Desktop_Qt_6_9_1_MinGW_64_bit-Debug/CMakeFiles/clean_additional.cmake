# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Dona_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Dona_autogen.dir\\ParseCache.txt"
  "Dona_autogen"
  )
endif()
