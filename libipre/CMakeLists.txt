

set(SOURCES
  space.cpp
  block.cpp
  stmt.cpp
)




include_directories(./)
include_directories(../)
add_library("ipre" ${SOURCES})
#add_executable("testIPRE" testGBDN.cpp)
#target_link_libraries("testIPRE" "gbdn" "tok")




