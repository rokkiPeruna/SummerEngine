//For memory management
#include <vld.h>

//Essential includes
#include <string>
#include <memory>
#include <core/Engine.h>



//For CMake
#define SE_CMAKE_CURRENT_PROJECT_NAME "@SummerGame@"

int main(int argc, char *argv[])
{
	//Print enviroment arguments to console
	for (int i = 0; i < argc; ++i)
		std::cout << *argv[i] << std::endl;

	//try
	//{
		///This is the name of the current project. Name MUST match folder name for desired project in 'projects/' folder. 
		//SE_TODO: Get 'tinydir' or other library for handling directories and files, so that user can create new projects straigth in the GUI
		const std::string CURRENT_PROJECT_NAME = "SummerGame";
		//
		se::priv::Engine SE_Engine(CURRENT_PROJECT_NAME);
		SE_Engine.Initialize();
		SE_Engine.EngineUpdate();
		SE_Engine.Uninitialize();
	//}
	//catch (...)
	//{
	//	std::cout << "Engine failed to unhandled exception!!!";
	//}
	return 0;

}