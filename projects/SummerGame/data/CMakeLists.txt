#root/projects/CURRENT_PROJECT/data

include_directories(${PROJECT_SOURCE_DIR}/engine/include)

set(USER_GAMELOGIC_DATA 
	${PROJECT_SOURCE_DIR}/projects/${SE_CURRENT_PROJECT_NAME}/data/resources/gamelogic/AddLogicToEngine.h
	${PROJECT_SOURCE_DIR}/projects/${SE_CURRENT_PROJECT_NAME}/data/resources/gamelogic/PlayerLogic.h
	${PROJECT_SOURCE_DIR}/projects/${SE_CURRENT_PROJECT_NAME}/data/resources/gamelogic/PlayerLogic.cpp
	)
set(USER_SCRIPT_DATA 
	${PROJECT_SOURCE_DIR}/projects/${SE_CURRENT_PROJECT_NAME}/data/resources/scripts/ScriptDeclarations.h
	${PROJECT_SOURCE_DIR}/projects/${SE_CURRENT_PROJECT_NAME}/data/resources/scripts/ShootProjectile.cpp
	)

source_group("userdata" FILES ${USER_GAMELOGIC_DATA})
source_group("userdata" FILES ${USER_SCRIPT_DATA})

add_library(user_data
	${USER_GAMELOGIC_DATA}
	${USER_SCRIPT_DATA}
	)
	
set_property(TARGET user_data PROPERTY FOLDER "user_data")

set_target_properties(user_data PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/executables)