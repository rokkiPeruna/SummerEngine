
#ifndef SE_RENDER_H
#define SE_RENDER_H

//External includes:
#include <glm/gtc/matrix_transform.hpp>

//SE includes
#include <core/Engine.h>
#include <gui/gui_values.h>
#include <renderers/Camera.h>
#include <renderers/RenderBatch.h>
#include <managers/Entity.h>
#include <managers/Resource.h>
#include <utility/Typedefs.h>
#include <utility/Math.h>


namespace se
{
namespace priv
{


class Render
{
public:
	///Default constructor.
	///1.param: pointer to Engine -class
	Render(Engine& engine_ref):m_engine(engine_ref) {};

	virtual ~Render(){}

	virtual void Initialize() = 0;
	virtual void Uninitialize() = 0;

	virtual void Update(SEfloat deltaTime) = 0;

	virtual void OnEntityAdded(const Entity& entity) = 0;

	virtual void OnEntityRemoved(const Entity& entity) = 0;

 	virtual void OnRendableComponentChanged(const Entity& entiy) = 0;

	virtual void ClearRenderBatches() = 0;

	using batch_values = std::tuple<SEuint, SEuint, SEuint>;

protected:
	///Reference to Engine -class
	Engine& m_engine;


};

}// !namespace priv
}// !namespace se

#endif //! SE_RENDER_H