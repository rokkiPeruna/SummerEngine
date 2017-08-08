#ifndef SE_GAME_RENDER_H
#define SE_GAME_RENDER_H

//Include standard library
#include <vector>

//Include external

//Include SE
#include <core/Render.h>

namespace se
{

namespace priv
{

struct StaticRenderBatch //FOR single element at this point
{
	std::vector<SEint> entity_ids;

	SEuint vao;
	SEuint  num_indices = 0;
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

	StaticRenderBatch(SEuint _num_indices) : num_indices(_num_indices), vao(0)
	{
		assert(num_indices > 2);
		glGenVertexArrays(1, &vao);
	}

};

///Brief: Game Render is not drawing any debug stuff and will divide entities in static and 
///dynamic containers

class GameRender : public Render
{
public:
	///Default constructor.
	///1.param: pointer to Engine -class
	GameRender(Engine& engine_ref);

	~GameRender();

	GameRender(const GameRender&) = delete;
	void operator=(const GameRender&) = delete;

	void Initialize() override final;
	void Uninitialize() override final;

	void Update(SEfloat deltaTime) override final;

	void OnEntityAdded(const Entity& entity) override final;
	void OnRendableComponentChanged(const Entity&) override final;

private:

	///Render batches
	std::vector<StaticRenderBatch> m_stat_rend_batches;

	using batch_values = Vec3u;

	struct cmpr_batch_values
	{
		bool operator()(const batch_values& a, const batch_values& b) const
		{
			return a.x < b.x || a.y < b.y || a.z < b.z; //SE_TODO: Create better comparator
		}
	};

	///Map that binds render batch values to it's pointer
	std::map<batch_values, StaticRenderBatch*, cmpr_batch_values> m_batch_value_map;

	//testing
	ShaderResource* CurrentShader;
	
	void _createStaticBuffers(StaticRenderBatch staticBatch);


	
};

}// !namespace priv
}// !namespace se


#endif