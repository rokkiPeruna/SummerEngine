#ifndef SE_EDITOR_RENDER_H
#define SE_EDITOR_RENDER_H

//Include standard library


//Include external


//Include SE
#include <core/Render.h>



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

class EditorRender : public Render
{

public:
	///Default constructor.
	///1.param: pointer to Engine -class
	EditorRender(Engine* engine_ptr);

	~EditorRender();


	EditorRender(const EditorRender&) = delete;
	void operator=(const EditorRender&) = delete;
	
	void Initialize() override final;
	void Uninitialize() override final;

	void Update(SEfloat deltaTime) override final;

	///Checks if there is a batch for spesific type of entities. If there is this component will be added
	///if not new one will be created
	void OnEntityAdded(const Entity& entity) override final;
	
	///Checks if the component is rendable in the first place. If it is makes sure that
	///the batch is changed
	void OnRendableComponentChanged(const Entity& entiy) override final;

	void AddDynRenderBatch(DynRenderBatch&& batch)
	{
		m_dyn_rend_batches.emplace_back(batch);
	}


private:
	///Render batches
	std::vector<DynRenderBatch> m_dyn_rend_batches;

	using batch_values = Vec3u;
	
	struct cmpr_batch_values
	{
		bool operator()(const batch_values& a, const batch_values& b) const
		{
			return a.x < b.x || a.y < b.y || a.z < b.z;
		}
	};

	///Map that binds render batch values to it's pointer
	std::map<batch_values, DynRenderBatch*, cmpr_batch_values> m_batch_value_map;

	//testing
	ShaderResource* CurrentShader;

};



}// !namepsace priv

}// !namespace se



#endif // !SE_DEBUG_RENDERER_H