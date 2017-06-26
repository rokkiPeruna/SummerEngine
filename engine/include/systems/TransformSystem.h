#ifndef SE_TRANSFORMSYSTEM_H
#define SE_TRANSFORMSYSTEM_H

//STL includes:
#include <vector>

//SE includes:
#include <systems/ComponentSystem.h>
#include <components/CTransform2D.h>

namespace se
{
namespace priv
{
///Brief: TransformSystem handles TransformComponents and their data.
class TransformSystem : public ComponentSystem
{
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

	///Initialize new component and add it to container
	std::shared_ptr<priv::Component> InitializeNewComponent(priv::Component& component) override final;


private:
	///Container holding actual TransformComponents. Uses std::vector for memory layout benefits.
	std::vector<CTransform2D> m_components;

};
}//namespace priv
}//namespace se


#endif