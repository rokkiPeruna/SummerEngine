#root/external/Box2D

file(GLOB BOX2D_SOURCES
		"Collision/*.cpp"
		"Collision/Shapes/*.cpp"
		"Common/*.cpp"
		"Dynamics/.*cpp"
		"Dynamics/Contacts/.*cpp"
		"Dynamics/Joints/.*cpp"
		"Rope/.*cpp")
file(GLOB BOX2D_HEADERS
		"Box2D.h"
		"Collision/*.h"
		"Collision/Shapes/*.h"
		"Common/*.h"
		"Dynamics/.*h"
		"Dynamics/Contacts/.*h"
		"Dynamics/Joints/.*h"
		"Rope/.*h")
		
source_group("box2d_cpp" FILES ${BOX2D_SOURCES})
source_group("box2d_h" FILES ${BOX2D_HEADERS})
	
#Include folder where lib is and folder where headers are
#Box2D's include style is "Box2D/../../.." etc
include_directories(${PROJECT_SOURCE_DIR}/libs
					${PROJECT_SOURCE_DIR}/external
					${PROJECT_SOURCE_DIR}/external/Box2D)	


#Create static library (.lib)
add_library(box2d ${BOX2D_SOURCES} ${BOX2D_HEADERS})

#Make sure the compiler can find include files for box2d when other libraries or executables link to box2d
target_include_directories(box2d PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_property(TARGET box2d PROPERTY FOLDER "libraries")


#Put static library to libs -folder
set_target_properties(box2d PROPERTIES
		ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/libs)
