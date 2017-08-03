#ifndef SE_EDITOR_RENDER_H
#define SE_EDITOR_RENDER_H

//Include standard library


//Include external


//Include SE
#include <systems/TransformSystem.h>
#include <managers/ResourceManager.h>


///Brief : Editor render won't create any static objects and will draw lines even to shapes 
/// which would not othewise be drawn. 

// TODO : highlight selected

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

struct DynRenderBatch //FOR single element at this point
{
	SEint entity_id;

	SEuint vao;

	SEuint  num_indices = 0;

	SEuint texture_handle = -1;

	SEuint pos_buffer = -1;
	SEuint ind_buffer = -1;
	SEuint texco_buffer = -1;
	SEuint col_buffer = -1;

	SEuint CreateBuffer(SEuint& buf, SEuint sz_of_buf, void* data, SEbool is_elem_array = false)
	{
		glBindVertexArray(vao);

		glGenBuffers(1, &buf);
		glBindBuffer((is_elem_array) ? GL_ARRAY_BUFFER : GL_ELEMENT_ARRAY_BUFFER, buf);
		glBufferData((is_elem_array) ? GL_ARRAY_BUFFER : GL_ELEMENT_ARRAY_BUFFER, sz_of_buf, data, GL_DYNAMIC_DRAW);
		glBindBuffer((is_elem_array) ? GL_ARRAY_BUFFER : GL_ELEMENT_ARRAY_BUFFER, 0);

		return buf;
	}

	void BindAttribPtr(SHADER_ATTRIB_INDEX shrd_atr_ind, SEuint num_vert_data_elem, void* data)
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
		/*else if (shrd_atr_ind == SHADER_ATTRIB_INDEX::INDICES)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ind_buffer);
			SEuint attr = static_cast<SEuint>(shrd_atr_ind);
			glEnableVertexAttribArray(attr);
			glVertexAttribPointer(attr, num_vert_data_elem, GL_FLOAT, GL_FALSE, num_vert_data_elem * sizeof(SEushort), 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}*/
	}

	DynRenderBatch(SEint _entity_id, SEuint _num_indices) : entity_id(_entity_id) ,num_indices(_num_indices), vao(0)
	{
		assert(num_indices > 2);
		glGenVertexArrays(1, &vao);
	}

};

class EditorRender
{

public:

	EditorRender();

	~EditorRender();


	EditorRender(const EditorRender&) = delete;
	void operator=(const EditorRender&) = delete;
	
	void Initialize();
	void Uninitialize();

	void Update(SEfloat deltaTime);
	void OnEntityAdded(const Entity& entity);
	void OnEntityRemoved();

	void AddDynRenderBatch(DynRenderBatch&& batch)
	{
		m_dyn_rend_batches.emplace_back(batch);
	}

	DynRenderBatch* GetDynRenderBatch(SEint entity_id)
	{
		for (auto rb : m_dyn_rend_batches)
		{
			if (rb.entity_id == entity_id)
				return &rb;
		}
		return nullptr;
	}

private:
	///
	std::vector<DynRenderBatch> m_dyn_rend_batches;

	//testing
	ShaderResource* CurrentShader;

};



}// !namepsace priv

}// !namespace se



#endif // !SE_DEBUG_RENDERER_H