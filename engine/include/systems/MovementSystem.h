#ifndef SE_MOVEMENTSYSTEM_H
#define SE_MOVEMENTSYSTEM_H


//SE includes:
#include <systems/ComponentSystem.h>
#include <components/CPosition.h>
#include <components/CVelocity.h>

namespace se
{
///Brief: User interface methods for MovementSystem. Implemantation in MovementSystemUiImpl.cpp
///
///Query CPosition -component with Entity's id. Returns pointer to component if found, nullptr otherwise
CPosition* GetCPosition(SEuint owner_id);
///Query CVelocity -component with Entity's id. Returns pointer to component if found, nullptr otherwise
CVelocity* GetCVelocity(SEuint owner_id);

///Add CPosition -component to Entity. Takes in Entity's id and built-in-place CPosition object
CPosition* AddCPosition(SEuint owner_id, CPosition component);
///Add CVelocity -component to Entity. Takes in Entity's id and built-in-place CVelocity object
CVelocity* AddCVelocity(SEuint owner_id, CVelocity component);

namespace priv
{
///Brief: MovementSystem handles components that are related to movement, such as CVelocity and CPosition. It has also
///containers for it's related components
class MovementSystem : public ComponentSystem
{
	//Friend user interface functions. Note the namespace identifier!
	friend CPosition* se::GetCPosition(SEuint owner_id);
	friend CVelocity* se::GetCVelocity(SEuint owner_id);
	friend CPosition* se::AddCPosition(SEuint owner_id, CPosition component);
	friend CVelocity* se::AddCVelocity(SEuint owner_id, CVelocity component);

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

private:
	///
	CPosition* _createCPositionComponent(CPosition& component);
	CVelocity* _createCVelocityComponent(CVelocity& component);

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