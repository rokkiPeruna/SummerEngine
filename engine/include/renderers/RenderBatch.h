#ifndef SUMMER_ENGINE_RENDER_BATCH_SE
#define SUMMER_ENGINE_RENDER_BATCH_SE

//include standard library
#include <vector>

//include external
#include <GLES3/glew.h>

//include se
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

struct RenderBatch
{
	RenderBatch(SEuint _num_indices = 0);

	SEuint num_indices;

	SEuint vao;

	SEuint texture_handle;

	SEuint pos_buffer;
	SEuint ind_buffer;
	SEuint texco_buffer;
	SEuint col_buffer;

	std::vector<SEint> entity_ids;


	SEuint CreateBuffer(SEuint& buf, SEuint sz_of_buf, void* data, SEbool is_elem_array = false);


	void BindAttribPtr(SHADER_ATTRIB_INDEX shrd_atr_ind, SEuint num_vert_data_elem);

};

struct DynamicRenderBatch : public RenderBatch
{
	DynamicRenderBatch(SEuint num_indices);
};

// ADD TO OWN CLASSES | HEADER 
struct StaticRenderBatch : public RenderBatch
{

	SEushort index_offset;
	SEushort offset_size;

	///Contains all position data from evry entity which belongs to this batch
	///This data is already translated with model matrix
	std::vector<Vec3f> position_container;

	///Contains all indice data from every entity which belongs to this batch
	std::vector<SEushort> indice_container;

	///Contains all color data from every entity which belongs to this batch
	std::vector<Vec4f> color_container;

	///Containes all texture data from every entity which belongs to this batch
	std::vector<Vec2f> texture_coordinate_container;

	StaticRenderBatch(SEuint _num_indices);

};

}//! namespace se
}//! namespace priv

#endif//! SE_RENDER_BATCH_SE
