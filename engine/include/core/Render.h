#ifndef SE_RENDER_H
#define SE_RENDER_H

///STL includes:
#include <vector>

//External includes:
#include <glm/gtc/matrix_transform.hpp>

//SE includes
#include <core/Engine.h>
#include <gui/gui_values.h>
#include <core/Camera.h>
#include <GLES3/glew.h>
#include <managers/Entity.h>
#include <managers/Resource.h>
#include <utility/Typedefs.h>
#include <utility/Math.h>


namespace se
{
namespace priv
{
enum class SHADER_ATTRIB_INDEX : SEuint
{
	POSITION,
	COLOR,
	TEX_COORDS,
	INDICES
};

///Brief: Virtual base class for all other renders (renderers)
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

protected:
	///Reference to Engine -class
	Engine& m_engine;

	// SE_TODO : Add some logic to engine (set / get current render etc..)
	//(atm engine is hevaily being modified)

};

}// !namespace priv
}// !namespace se

#endif //! SE_RENDER_H