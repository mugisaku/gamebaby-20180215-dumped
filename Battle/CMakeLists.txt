

set(SOURCES
  TemporaryData.cpp
  SystemData.cpp
  SavedData.cpp
  ReadOnlyData.cpp
  FrontInterface.cpp
  Screen.cpp
  Startup_PartyMaking.cpp
  Startup_CharacterMaking.cpp
  Startup_ClassChoosing.cpp
  Startup_NameMaking.cpp
  Battle.cpp
  BattleTeam.cpp
  BattlePlayer.cpp
  BattlePlayerBase.cpp
  BattleEnemy.cpp
  BattleEnemyParty.cpp
  BattleCommand.cpp
  BattleTimeData.cpp
  Battle_StreamText.cpp
  Battle_ActionMaking.cpp
  Battle_ActionProcessing.cpp
)




add_subdirectory(process_list_collection)

include_directories(./)
include_directories(../)
include_directories(../Standard)
include_directories(../libgbdn)
include_directories(../libtok)
add_library("battle" ${SOURCES})
target_link_libraries("battle" "process_list_collection")




