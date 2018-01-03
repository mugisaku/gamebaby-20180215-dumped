

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
  process_lists/attack.cpp
)




include_directories(./)
include_directories(../)
add_library("battle" ${SOURCES})




