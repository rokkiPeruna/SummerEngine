#ifndef SE_MOVEMENTSYSTEM_H
#define SE_MOVEMENTSYSTEM_H


//SE includes:
#include <systems/ComponentSystem.h>
#include <components/CPosition.h>
#include <components/CVelocity.h>

namespace se
{
namespace priv
{
///Brief: MovementSystem handles components that are related to movement, such as CVelocity and CPosition. It has also
///containers for it's related components
class MovementSystem : public ComponentSystem
{
public:
	///Default constructor
	MovementSystem();
	///Destructor
	~MovementSystem();
	///Deleted copy constructor and assign operator
	MovementSystem(const MovementSystem&) = delete;
	void operator=(const MovementSystem&) = delete;

	///Initialize system
	void Initialize() override final;

	///Uninitialize system
	void Uninitialize() override final;

	///Run through logic using components as values
	void Update(float deltaTime) override final;

	///Clear component containers
	void ClearComponentContainers() override final;

	///OnEntityAdded checks if entity has components that need to be builded to this system
	void OnEntityAdded(Entity& e, SceneFileFormatIterator& entity_obj) override final;

	void OnEntityRemoved(Entity& e, SceneFileFormatIterator& entity_obj) override final;

	///Creates component to entity and add it to container and json object
	SEuint CreateComponent(Entity& entity, COMPONENT_TYPE component_type, SceneFileFormatIterator& itr) override final;

private:

	///Component containers
	std::vector<CPosition> m_cpositions;
	std::vector<CVelocity> m_cvelocities;

	///Components maps. Store component pointers in maps with owner ids as keys
	std::unordered_map<SEuint, CPosition*> m_cpositions_map;
	std::unordered_map<SEuint, CVelocity*> m_cvelocities_map;

};
}//namespace priv
}//namespace se


#endif