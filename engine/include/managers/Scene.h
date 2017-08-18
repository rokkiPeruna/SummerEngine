#ifndef SUMMER_ENGINE_SCENE_H
#define SUMMER_ENGINE_SCENE_H

///STL includes:
#include <string>

//External includes:
#include <nlohmann_json/json.hpp>

///SE includes:
#include <utility/Typedefs.h>

namespace se
{
namespace priv
{
///Brief: SceneType is a enum defining what type scene is
enum class SCENE_TYPE : SEint
{
	FAULTY = -1,
	PROPER
};

///Brief: Scene -class represents one scene in game, e.g. main menu, levels, credits etc.
///It holds entities through EntityComponentManager object and handles scene loading and saving
///from/to json files.
class Scene
{
public:
	///Default constructor. Takes in string for scene name
	Scene(std::string sceneName, SCENE_TYPE type, SEuint width, SEuint heigth);
	///Destructor
	~Scene();
	///Copy constructor
	Scene(const Scene&);
	///Deleted assign operator
	void operator=(const Scene&);

	//SE_TODO: Add move operations

	///Load resources to current scene

	///Load entities


	///Getters for variables
	std::string GetName() const;
	nlohmann::json* GetData();
	SCENE_TYPE GetType() const;
	SEuint GetWidth() const;
	SEuint GetHeigth() const;

	void SetData(nlohmann::json* j);

private:
	///Name of the scene
	std::string m_name;

	///Json object holding scene data
	nlohmann::json* m_data;

	///Type of the scene
	SCENE_TYPE m_type;

	///Width and heigth
	SEuint m_width;
	SEuint m_heigth;

};

}//namespace priv
}//namespace se


#endif