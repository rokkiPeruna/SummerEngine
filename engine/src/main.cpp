
//For memory management
#include <vld.h>

//
#include <core/Engine.h>


int main(int argc, char *argv[])
{
	///This is the name of the current project. Name MUST match folder name for desired project in 'projects/' folder. 
	//SE_TODO: Get 'tinydir' or other library for handling directories and files, so that user can create new projects straigth in the GUI
	const std::string CURRENT_PROJECT_NAME = "SummerGame";
	//
	se::priv::Engine& SE_Engine = se::priv::Engine::Instance();
	SE_Engine.Initialize(CURRENT_PROJECT_NAME);
	SE_Engine.EngineUpdate();
	SE_Engine.Uninitialize();
	return 0;

}