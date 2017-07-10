#include <managers/Scene.h>

namespace se
{
namespace priv
{
Scene::Scene(std::string sceneName, SCENE_TYPE type, SEuint width, SEuint heigth)
	: m_name(sceneName)
	, m_data(nullptr)
	, m_type(type)
	, m_width(width)
	, m_heigth(heigth)
{
}

Scene::~Scene()
{
}

Scene::Scene(const Scene& o)
	: m_name(o.m_name)
	, m_data(o.m_data)
	, m_type(o.m_type)
	, m_width(o.m_width)
	, m_heigth(o.m_heigth)
{
}

void Scene::operator=(const Scene& o)
{
	m_name = o.m_name;
	m_data = o.m_data;
	m_type = o.m_type;
	m_width = o.m_width;
	m_heigth = o.m_heigth;
}

std::string Scene::GetName()
{
	return m_name;
}

nlohmann::json* Scene::GetData()
{
	return m_data;
}

SCENE_TYPE Scene::GetType()
{
	return m_type;
}

SEuint Scene::GetWidth()
{
	return m_width;
}

SEuint Scene::GetHeigth()
{
	return m_heigth;
}

void Scene::SetData(nlohmann::json* j)
{
	m_data = j;
}

}//namespace priv
}//namespace se