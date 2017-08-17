
#ifndef SUMMER_ENGINE_RENDER_H
#define SUMMER_ENGINE_RENDER_H

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
	Render(Engine& engine_ref);
	//
	virtual ~Render() = default;
	Render(const Render&) = delete;
	void operator=(const Render&) = delete;
	Render(Render&&) = delete;
	void operator=(Render&&) = delete;

	virtual void Initialize() = 0;
	virtual void Uninitialize() = 0;

	virtual void Update(SEfloat deltaTime) = 0;

	virtual void OnEntityAdded(const Entity& entity) = 0;

	virtual void OnEntityRemoved(const Entity& entity) = 0;

 	virtual void OnRendableComponentChanged(const Entity& entiy) = 0;

	virtual void ClearRenderBatches() = 0;

	static void SetPerspMatrix(Mat4f perspective_matrix);
	static void SetPerspMatrix(SEfloat fov_as_deg, SEfloat ratio, SEfloat near_z, SEfloat far_z);

protected:
	///Reference to Engine -class
	Engine& m_engine;

	///Perspective matrix
	static Mat4f m_perps_matrix;
};

}// !namespace priv
}// !namespace se

#endif //! SE_RENDER_H