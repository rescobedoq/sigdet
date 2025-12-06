# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\TO-Donaciones_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\TO-Donaciones_autogen.dir\\ParseCache.txt"
  "TO-Donaciones_autogen"
  )
endif()
