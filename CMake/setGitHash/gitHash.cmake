set(CMD0 date -u +%Y%m%d%H%M%S)
set(CMD1 git rev-parse HEAD)
set(CMD2 tr -d '\n')

execute_process(COMMAND ${CMD0} COMMAND ${CMD2} OUTPUT_VARIABLE DATE)
execute_process(COMMAND ${CMD1} COMMAND ${CMD2} OUTPUT_VARIABLE GIT_HASH)

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/githash.cpp.in" 
  "${CMAKE_CURRENT_BINARY_DIR}/githash.cpp" @ONLY)

