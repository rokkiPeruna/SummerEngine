#ifndef SE_SCENE_H
#define SE_SCENE_H

///STL includes:
#include <string>

//External includes:
#include <nlohmann_json/json.hpp>

///SE includes:
#include <managers/EntityComponentManager.h>

namespace se
{
namespace priv
{
///Brief: SceneType is a enum defining what type scene is
enum class SCENE_TYPE : SEint
{
	FAULTY = -1,
	MENU = 1,
	LEVEL,
	CREDITS
};

///Brief: Scene -class represents one scene in game, e.g. main menu, levels, credits etc.
///It holds entities through EntityComponentManager object and handles scene loading and saving
///from/to json files.
class Scene
{
public:
	///Default constructor. Takes in string for scene name
	Scene(std::string sceneName, SCENE_TYPE type, SEint id, SEuint width, SEuint heigth);
	///Destructor
	~Scene();
	///Copy constructor
	Scene(const Scene&);
	///Deleted assign operator
	void operator=(const Scene&) = delete;

	///Load resources to current scene

	///Load entities


	///Getters for variables
	std::string GetName();
	SCENE_TYPE GetType();
	SEint GetID();
	SEuint GetWidth();
	SEuint GetHeigth();

private:
	///Name of the scene
	std::string m_name;

	///Type of the scene
	SCENE_TYPE m_type;

	///Id as SEint
	SEint m_id;

	///Width and heigth
	SEuint m_width;
	SEuint m_heigth;

};

}//namespace priv
}//namespace se


#endif