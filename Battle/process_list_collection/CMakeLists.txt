

set(SOURCES
  attack.cpp
)




include_directories(./)
include_directories(../)
include_directories(../../)
include_directories(../../Standard)
include_directories(../../libgbdn)
include_directories(../../libtok)
add_library("process_list_collection" ${SOURCES})




