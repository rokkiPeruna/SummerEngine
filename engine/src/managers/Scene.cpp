#include <managers/Scene.h>

namespace se
{
namespace priv
{
Scene::Scene(std::string sceneName, SCENE_TYPE type)
	: m_name(sceneName)
	, m_type(type)
	, m_id(0)
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

SEint Scene::GetID()
{
	return m_id;
}

}//namespace priv
}//namespace se