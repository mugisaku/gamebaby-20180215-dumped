

set(SOURCES
  make_token_list.cpp
  token.cpp
  stream_reader.cpp
  stream_reader__skip.cpp
  stream_reader__read_number.cpp
)




include_directories(./)
add_library("tok" ${SOURCES})
add_executable("testTOK" testTOK.cpp)
target_link_libraries("testTOK" "tok")




