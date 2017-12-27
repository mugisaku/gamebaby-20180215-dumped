

set(SOURCES
  string.cpp
  list.cpp
  value.cpp
)




include_directories(./)
include_directories(../)
add_library("gbdn" ${SOURCES})
add_executable("testGBDN" testGBDN.cpp)
target_link_libraries("testGBDN" "gbdn" "tok")




