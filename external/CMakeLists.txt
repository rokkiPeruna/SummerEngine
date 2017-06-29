#root/external/

#Sub-directories having CMakeLists
add_subdirectory(Box2D)
add_subdirectory(OpenGL)
add_subdirectory(SDL2)
#add_subdirectory(OpenAL)

#Include directories
include_directories(SDL2/include)
include_directories(Box2D)
include_directories(STB)
include_directories(glm)
include_directories(nlohmann_json)
include_directories(OpenGL)
include_directories(OpenGL/EGL)
include_directories(OpenGL/GLES2)
include_directories(OpenGL/GLES3)
include_directories(OpenGL/KHR)
include_directories(imgui)
#include_directories(OpenAL)

