

set(SOURCES
  device.cpp
  device__square_wave.cpp
  device__noise.cpp
  stmt.cpp
  expr.cpp
  block.cpp
  routine.cpp
  expr__unary_operation.cpp
  expr__binary_operation.cpp
  execution_context.cpp
  execution_frame.cpp
  value.cpp
)




include_directories(./)
include_directories(../)
add_library("gbsnd" ${SOURCES})




