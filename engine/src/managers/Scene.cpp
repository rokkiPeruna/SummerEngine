#include <managers/Scene.h>

namespace se
{
namespace priv
{
Scene::Scene(std::string sceneName, SCENE_TYPE type)
	: m_name(sceneName)
	, m_type(type)
{


}

Scene::~Scene()
{

}


std::string Scene::GetName()
{
	return m_name;
}

SCENE_TYPE Scene::GetType()
{
	return m_type;
}

}//namespace priv
}//namespace se