

set(SOURCES
  type_decl.cpp
  type_info.cpp
  type_info__constructor.cpp
  type_info__is.cpp
  type_info__make.cpp
  type_info__add.cpp
  type_info__remove.cpp
  type_info__print.cpp
  array_def.cpp
  enum_def.cpp
  struct_def.cpp
  union_def.cpp
)




include_directories(./)
include_directories(../)
add_library("ty" ${SOURCES})
add_executable("testTY" testTY.cpp)
target_link_libraries("testTY" "ty")




