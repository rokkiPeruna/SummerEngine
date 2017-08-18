#root/projects/CURRENT_PROJECT/data

include_directories(${PROJECT_SOURCE_DIR}/engine/include)
include_directories(${PROJECT_SOURCE_DIR}/external/STB)
include_directories(${PROJECT_SOURCE_DIR}/external)
include_directories(${PROJECT_SOURCE_DIR}/external/imgui)
include_directories(${PROJECT_SOURCE_DIR}/external/OpenGL)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/resources)

set(USER_GAMELOGIC_DATA 
	resources/gamelogic/AddLogicToEngine.h
	resources/gamelogic/PlayerLogic.h
	resources/gamelogic/PlayerLogic.cpp
	resources/gamelogic/EnemyLogic.h
	resources/gamelogic/EnemyLogic.cpp
	)
set(USER_SCRIPT_DATA 
	resources/scripts/ScriptDeclarations.h
	resources/scripts/ShootProjectile.cpp
	)
set(USER_EVENTS_DATA
	resources/userevents/UserEvents1.h
	resources/userevents/UserEvents2.h
	resources/userevents/UserEvents3.h
	resources/userevents/UserEvents4.h
	)

source_group("gamelogic" FILES ${USER_GAMELOGIC_DATA})
source_group("scripts" FILES ${USER_SCRIPT_DATA})
source_group("events" FILES ${USER_EVENTS_DATA})

add_library(user_data
	${USER_GAMELOGIC_DATA}
	${USER_SCRIPT_DATA}
	${USER_EVENTS_DATA}
	)
	
set_property(TARGET user_data PROPERTY FOLDER "user_data")

set_target_properties(user_data PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/executables)