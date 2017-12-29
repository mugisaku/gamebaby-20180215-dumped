

set(SOURCES
  SawtoothCharacterBuffer.cpp
  LinearCharacterBuffer.cpp
  unicode.cpp
  environment.cpp
  RandomNumber.cpp
  Controller.cpp
  LineMaker.cpp
  Routine.cpp
  Task.cpp
  GroupTask.cpp
  Window.cpp
  Window__draw_frame.cpp
  Menu.cpp
  ScrollStyleMenuWindow.cpp
  ColumnStyleMenuWindow.cpp
  StringBuffer.cpp
  Stream.cpp
  StreamReader.cpp
  StreamWriter.cpp
  Image.cpp
  Image__png.cpp
  Image__draw.cpp
  Image__transfer.cpp
  Image__print.cpp
  GlyphSet.cpp
)




include_directories(./)
include_directories(../)
add_library("gbdn" ${SOURCES})
add_executable("testGBDN" testGBDN.cpp)
target_link_libraries("testGBDN" "gbdn" "tok")




