#include <managers/Scene.h>

namespace se
{
namespace priv
{
Scene::Scene(std::string sceneName, SCENE_TYPE type, SEint id, SEuint width, SEuint heigth)
	: m_name(sceneName)
	, m_type(type)
	, m_id(id)
	, m_width(width)
	, m_heigth(heigth)
{
}

Scene::~Scene()
{
}

Scene::Scene(const Scene& o)
	: m_name(o.m_name)
	, m_type(o.m_type)
	, m_id(o.m_id)
	, m_width(o.m_width)
	, m_heigth(o.m_heigth)
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

SEuint Scene::GetWidth()
{
	return m_width;
}

SEuint Scene::GetHeigth()
{
	return m_heigth;
}

}//namespace priv
}//namespace se