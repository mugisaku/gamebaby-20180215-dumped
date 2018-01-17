

set(SOURCES
  device.cpp
  device__square_wave.cpp
  device__noise.cpp
  stmt.cpp
  expr.cpp
  expr__make_expr.cpp
  operand.cpp
  expr__unary_operation.cpp
  expr__binary_operation.cpp
  block.cpp
  routine.cpp
  execution_context.cpp
  execution_frame.cpp
  value.cpp
  tree_node.cpp
  tree_block.cpp
  script.cpp
  script_token.cpp
  script_token_string.cpp
)




include_directories(./)
include_directories(../)
add_library("gbsnd" ${SOURCES})




