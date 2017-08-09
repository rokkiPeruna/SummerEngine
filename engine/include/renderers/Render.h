
#ifndef SE_RENDER_H
#define SE_RENDER_H

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


// ADD TO OWN CLASSES | HEADER 
struct StaticRenderBatch //FOR single element at this point
{
	std::vector<SEint> entity_ids;

	SEushort index_offset = SEushort_max;
	SEushort offset_size;

	SEuint vao;
	SEuint num_indices = 0;
	SEuint texture_handle = SEuint_max;

	SEuint pos_buffer = SEuint_max;
	SEuint ind_buffer = SEuint_max;
	SEuint texco_buffer = SEuint_max;
	SEuint col_buffer = SEuint_max;

	///Contains all position data from evry entity which belongs to this batch
	///This data is already translated with model matrix
	std::vector<Vec3f> position_container;

	///Contains all indice data from every entity which belongs to this batch
	std::vector<SEushort> indice_container;

	///Contains all color data from every entity which belongs to this batch
	std::vector<Vec4f> color_container;

	///Containes all texture data from every entity which belongs to this batch
	std::vector<Vec2f> texture_coordinate_container;

	//			to be created buffer  | size of the buffer | buffer data | flags
	SEuint CreateBuffer(SEuint& buf, SEuint sz_of_buf, void* data, SEbool is_elem_array = false)
	{
		glBindVertexArray(vao);

		glGenBuffers(1, &buf);
		glBindBuffer((is_elem_array) ? GL_ARRAY_BUFFER : GL_ELEMENT_ARRAY_BUFFER, buf);
		glBufferData((is_elem_array) ? GL_ARRAY_BUFFER : GL_ELEMENT_ARRAY_BUFFER, sz_of_buf, data, GL_STATIC_DRAW);
		glBindBuffer((is_elem_array) ? GL_ARRAY_BUFFER : GL_ELEMENT_ARRAY_BUFFER, 0);

		return buf;
	}

	void BindAttribPtr(SHADER_ATTRIB_INDEX shrd_atr_ind, SEuint num_vert_data_elem)
	{
		glBindVertexArray(vao);

		if (shrd_atr_ind == SHADER_ATTRIB_INDEX::POSITION)
		{
			glBindBuffer(GL_ARRAY_BUFFER, pos_buffer);
			SEuint attr = static_cast<SEuint>(shrd_atr_ind);
			glEnableVertexAttribArray(attr);
			glVertexAttribPointer(attr, num_vert_data_elem, GL_FLOAT, GL_FALSE, num_vert_data_elem * sizeof(SEfloat), 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		else if (shrd_atr_ind == SHADER_ATTRIB_INDEX::COLOR)
		{
			glBindBuffer(GL_ARRAY_BUFFER, col_buffer);
			SEuint attr = static_cast<SEuint>(shrd_atr_ind);
			glEnableVertexAttribArray(attr);
			glVertexAttribPointer(attr, num_vert_data_elem, GL_UNSIGNED_BYTE, GL_TRUE, num_vert_data_elem * sizeof(SEchar), 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		else if (shrd_atr_ind == SHADER_ATTRIB_INDEX::TEX_COORDS)
		{
			glBindBuffer(GL_ARRAY_BUFFER, texco_buffer);
			SEuint attr = static_cast<SEuint>(shrd_atr_ind);
			glEnableVertexAttribArray(attr);
			glVertexAttribPointer(attr, num_vert_data_elem, GL_FLOAT, GL_FALSE, num_vert_data_elem * sizeof(SEfloat), 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

	}

	StaticRenderBatch(SEuint _num_indices) : num_indices(_num_indices), vao(0)
	{
		assert(num_indices > 2);
		glGenVertexArrays(1, &vao);
	}

};

struct DynRenderBatch //FOR single element at this point
{
	std::vector<SEint> entity_ids;

	SEuint vao;
	SEuint  num_indices = 0;
	SEuint texture_handle = SEuint_max;

	SEuint pos_buffer = SEuint_max;
	SEuint ind_buffer = SEuint_max;
	SEuint texco_buffer = SEuint_max;
	SEuint col_buffer = SEuint_max;

	SEuint CreateBuffer(SEuint& buf, SEuint sz_of_buf, void* data, SEbool is_elem_array = false)
	{
		glBindVertexArray(vao);

		glGenBuffers(1, &buf);
		glBindBuffer((is_elem_array) ? GL_ARRAY_BUFFER : GL_ELEMENT_ARRAY_BUFFER, buf);
		glBufferData((is_elem_array) ? GL_ARRAY_BUFFER : GL_ELEMENT_ARRAY_BUFFER, sz_of_buf, data, GL_DYNAMIC_DRAW);
		glBindBuffer((is_elem_array) ? GL_ARRAY_BUFFER : GL_ELEMENT_ARRAY_BUFFER, 0);

		return buf;
	}

	void BindAttribPtr(SHADER_ATTRIB_INDEX shrd_atr_ind, SEuint num_vert_data_elem)
	{
		glBindVertexArray(vao);

		if (shrd_atr_ind == SHADER_ATTRIB_INDEX::POSITION)
		{
			glBindBuffer(GL_ARRAY_BUFFER, pos_buffer);
			SEuint attr = static_cast<SEuint>(shrd_atr_ind);
			glEnableVertexAttribArray(attr);
			glVertexAttribPointer(attr, num_vert_data_elem, GL_FLOAT, GL_FALSE, num_vert_data_elem * sizeof(SEfloat), 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		else if (shrd_atr_ind == SHADER_ATTRIB_INDEX::COLOR)
		{
			glBindBuffer(GL_ARRAY_BUFFER, col_buffer);
			SEuint attr = static_cast<SEuint>(shrd_atr_ind);
			glEnableVertexAttribArray(attr);
			glVertexAttribPointer(attr, num_vert_data_elem, GL_UNSIGNED_BYTE, GL_TRUE, num_vert_data_elem * sizeof(SEchar), 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		else if (shrd_atr_ind == SHADER_ATTRIB_INDEX::TEX_COORDS)
		{
			glBindBuffer(GL_ARRAY_BUFFER, texco_buffer);
			SEuint attr = static_cast<SEuint>(shrd_atr_ind);
			glEnableVertexAttribArray(attr);
			glVertexAttribPointer(attr, num_vert_data_elem, GL_FLOAT, GL_FALSE, num_vert_data_elem * sizeof(SEfloat), 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

	}

	DynRenderBatch(SEuint _num_indices) : num_indices(_num_indices), vao(0)
	{
		assert(num_indices > 2);
		glGenVertexArrays(1, &vao);
	}

};

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


};

}// !namespace priv
}// !namespace se

#endif //! SE_RENDER_H