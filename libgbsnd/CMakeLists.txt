

set(SOURCES
  device.cpp
  device__square_wave.cpp
)




include_directories(./)
include_directories(../)
add_library("gbsnd" ${SOURCES})




