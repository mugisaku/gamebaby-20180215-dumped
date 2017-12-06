

set(SOURCES
  string.cpp
  list.cpp
  value.cpp
  stream_reader.cpp
  stream_reader__skip.cpp
  stream_reader__read_number.cpp
)




include_directories(./)
add_library("gbdn" ${SOURCES})
add_executable("testlib" testlib.cpp)
target_link_libraries("testlib" "gbdn")




