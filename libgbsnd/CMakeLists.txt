

set(SOURCES
  device.cpp
  device__square_wave.cpp
  device__noise.cpp
  stmt.cpp
  expr_element.cpp
  expr_array.cpp
  data_stack.cpp
  operation.cpp
  operand.cpp
  block.cpp
  routine.cpp
  execution_context.cpp
  reference.cpp
  property.cpp
  value.cpp
  shared_string.cpp
  script.cpp
  script_token.cpp
  script_token_string.cpp
  script_token_cursor.cpp
)




include_directories(./)
include_directories(../)
add_library("gbsnd" ${SOURCES})




