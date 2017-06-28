#ifndef SE_TRANSFORMSYSTEM_H
#define SE_TRANSFORMSYSTEM_H

//STL includes:
#include <vector>

//SE includes:
#include <systems/ComponentSystem.h>
#include <components/CTransform2D.h>

namespace se
{
///Brief: Global function that work as interface for user to add and modify components.
///Returns pointer to CTransform2D -component matching the owner id. Returns nullptr if owner
///doesn't have that component.
CTransform2D* GetTransform2D(SEuint owner_id);

///Brief: Global function that work as interface for user to add and modify components.
///Takes in owner id and CTransform2D component which can be build in place.
///Retunrs pointer to the newly created component.
CTransform2D* AddTransform2D(SEuint owner_id, CTransform2D& component);

namespace priv
{
///Brief: TransformSystem handles TransformComponents and their data.
class TransformSystem : public ComponentSystem
{
	///Friend user interface functions
	friend CTransform2D* se::GetTransform2D(SEuint);
	friend CTransform2D* se::AddTransform2D(SEuint owner_id, CTransform2D& component);
public:
	///Default constructor. Takes in shared_ptr of EntityComponentManager.
	TransformSystem();
	///Destructor
	~TransformSystem();
	///No copies allowed
	//TransformSystem(const TransformSystem&) = delete;
	void operator=(const TransformSystem&) = delete;


	///Initialize
	void Initialize() override final;

	///Uninitialize
	void Uninitialize() override final;

	///Updates TransformComponents
	void Update(SEfloat deltaTime) override final;


private:
	///Initialize new component and add it to container. Return shared_ptr
	CTransform2D* _createComponent(CTransform2D& component);

	///Container holding actual TransformComponents. Uses std::vector for memory layout benefits.
	std::vector<CTransform2D> m_components;

	///Static container holding pointers to component and their owner id as key
	static std::map<SEuint, CTransform2D*> m_component_map;
};
}//namespace priv
}//namespace se


#endif