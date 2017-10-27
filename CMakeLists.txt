cmake_minimum_required(VERSION 2.8)
project(gmbb)


find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "CCACHE_DIR=/tmp/ccachedir ccache")
endif(CCACHE_FOUND)


set(CMAKE_VERBOSE_MAKEFILE ON)


if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()


set(CMAKE_C_COMPILER  gcc)
set(CMAKE_C_FLAGS   "-std=c14 -Werror")
set(CMAKE_CXX_COMPILER  g++)
set(CMAKE_CXX_FLAGS "-std=c++14 -Werror")
set(CMAKE_CXX_LINK_FLAGS  "-lstdc++ -lz -lpng -lSDL2 -lSDL2main")


set(CMAKE_C_FLAGS_RELEASE   "${CMAKE_C_FLAGS}   -O2 -march=core2 -fomit-frame-pointer")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2 -march=core2 -fomit-frame-pointer")
set(CMAKE_C_FLAGS_DEBUG     "${CMAKE_C_FLAGS}   -Og -g")
set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS} -Og -g")


if(EMSC)
  set(EXECUTABLE_EXTENSION ".html")
  set(CMAKE_CXX_COMPILER  em++)
  set(CMAKE_CXX_FLAGS "-std=c++14 -Werror -Wno-switch -O2")
  set(CMAKE_CXX_FLAGS_DEBUG "")
  set(CMAKE_CXX_LINK_FLAGS  "${CMAKE_CXX_LINK_FLAGS} -s USE_ZLIB=1 -s USE_LIBPNG=1 -s USE_SDL=2 --embed-file image.png --embed-file script.sc --embed-file large_font.bin --embed-file small_font.bin")
endif()




set(GAME_SOURCES
  Game/Event.cpp
  Game/EventQueue.cpp
  Game/Actor.cpp
  Game/Director.cpp
  Game/EffectObject.cpp
  Game/Game.cpp
  Game/Game__Message.cpp
  Game/Game__MainMenu.cpp
  Game/Game__SackMenu.cpp
  Game/Game__Choosing.cpp
  Game/Game__StatusMonitor.cpp
  Game/Game__StatusReportor.cpp
  Game/Game__Debugger.cpp
  Game/Game__controll_hero_piece.cpp
  Game/Game__throw_item.cpp
  Game/Game__ScriptManager.cpp
  Game/Game__process_script.cpp
  Game/Game__process_event.cpp
  Game/GameData.cpp
  Game/GameItem.cpp
  Game/GameItemSpecs.cpp
  Game/Shop.cpp
  Game/Sack.cpp
  Game/Hero.cpp
  Game/Piece.cpp
  Game/Square.cpp
  Game/Board.cpp
  Game/Board__render.cpp
)


set(SCRIPT_SOURCES
  Script/gmbb_Script__List.cpp
  Script/gmbb_Script__Cursor.cpp
  Script/gmbb_Script__Value.cpp
  Script/gmbb_Script__StreamReader.cpp
  Script/gmbb_Script__StreamReader__read_number.cpp
)


set(STANDARD_SOURCES
  Standard/gmbb_unicode.cpp
  Standard/gmbb_environment.cpp
  Standard/gmbb_Storage.cpp
  Standard/gmbb_RandomNumber.cpp
  Standard/gmbb_LineMaker.cpp
  Standard/gmbb_Routine.cpp
  Standard/gmbb_Task.cpp
  Standard/gmbb_GroupTask.cpp
  Standard/gmbb_Window.cpp
  Standard/gmbb_Window__draw_frame.cpp
  Standard/gmbb_Text.cpp
  Standard/gmbb_MessageWindow.cpp
  Standard/gmbb_Menu.cpp
  Standard/gmbb_ScrollStyleMenuWindow.cpp
  Standard/gmbb_ColumnStyleMenuWindow.cpp
  Standard/gmbb_File.cpp
  Standard/gmbb_FileReader.cpp
  Standard/gmbb_FileWriter.cpp
  Standard/gmbb_Image.cpp
  Standard/gmbb_Image__png.cpp
  Standard/gmbb_Image__draw.cpp
  Standard/gmbb_Image__transfer.cpp
  Standard/gmbb_Image__print.cpp
  Standard/gmbb_GlyphSet.cpp
)




include_directories(./)
include_directories(./Script)
include_directories(./Standard)
include_directories(/usr/include/SDL2)
add_executable("testMain${EXECUTABLE_EXTENSION}" Game/testMain.cpp  ${SCRIPT_SOURCES} ${STANDARD_SOURCES} ${GAME_SOURCES})
add_executable("testScript${EXECUTABLE_EXTENSION}" Script/testScript.cpp ${SCRIPT_SOURCES})


if(EMSC)
add_custom_target(bincopy ALL COMMAND cp ../bin/image.png ./ COMMAND cp ../script.sc ./ COMMAND cp /usr/local/share/gmbb/* ./)
set_target_properties("testMain${EXECUTABLE_EXTENSION}"  PROPERTIES LINK_FLAGS "--shell-file ../shell.html")
endif()




