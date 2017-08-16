#root/projects/CURRENT_PROJECT/data

include_directories(${PROJECT_SOURCE_DIR}/engine/include)

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

source_group("userdata" FILES ${USER_GAMELOGIC_DATA})
source_group("userdata" FILES ${USER_SCRIPT_DATA})

add_library(user_data
	${USER_GAMELOGIC_DATA}
	${USER_SCRIPT_DATA}
	)
	
set_property(TARGET user_data PROPERTY FOLDER "user_data")

set_target_properties(user_data PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/executables)