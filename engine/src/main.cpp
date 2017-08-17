//For memory management
#include <vld.h>

//Essential includes
#include <string>
#include <iostream>
#include <cassert>
#include <core/Engine.h>



//For CMake
//#define SUMMER_ENGINE_CMAKE_CURRENT_PROJECT_NAME "@SummerGame@"

int main(int argc, char *argv[])
{
	//Print enviroment arguments to console
	for (int i = 0; i < argc; ++i)
		std::cout << *argv[i] << std::endl;

	//Read current project's name
	std::ifstream filedata("../../CurrentProject.txt");
	std::string project_name{};
	if (filedata.peek() != std::ifstream::traits_type::eof())
		while (!filedata.eof())
			std::getline(filedata, project_name);
	else
		assert(1 == 0);


	//try
	//{
		///This is the name of the current project. Name MUST match folder name for desired project in 'projects/' folder. 
		//SE_TODO: Get 'tinydir' or other library for handling directories and files, so that user can create new projects straigth in the GUI
	//
	se::priv::Engine SE_Engine(project_name);
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