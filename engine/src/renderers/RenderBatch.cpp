#include <renderers/RenderBatch.h>

namespace se
{
namespace priv
{

RenderBatch::RenderBatch(SEuint _num_indices)
	: num_indices(_num_indices)
	, vao(0)
	, texture_handle(SEuint_max)
	, pos_buffer(SEuint_max)
	, ind_buffer(SEuint_max)
	, texco_buffer(SEuint_max)
	, col_buffer(SEuint_max)
	, entity_ids(0)
{
	assert(num_indices > 2);
	glGenVertexArrays(1, &vao);
}

SEuint RenderBatch::CreateBuffer(SEuint& buf, SEuint sz_of_buf, void* data, SEbool is_elem_array)
{
	glBindVertexArray(vao);

	glGenBuffers(1, &buf);
	glBindBuffer((is_elem_array) ? GL_ARRAY_BUFFER : GL_ELEMENT_ARRAY_BUFFER, buf);
	glBufferData((is_elem_array) ? GL_ARRAY_BUFFER : GL_ELEMENT_ARRAY_BUFFER, sz_of_buf, data, GL_DYNAMIC_DRAW);
	glBindBuffer((is_elem_array) ? GL_ARRAY_BUFFER : GL_ELEMENT_ARRAY_BUFFER, 0);

	return buf;
}

void RenderBatch::BindAttribPtr(SHADER_ATTRIB_INDEX shrd_atr_ind, SEuint num_vert_data_elem)
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

StaticRenderBatch::StaticRenderBatch(SEuint _num_indices)
	: RenderBatch(_num_indices)
	, index_offset(SEushort_max)
	, offset_size(0)
{

}

DynamicRenderBatch::DynamicRenderBatch(SEuint _num_indices)
	: RenderBatch(_num_indices)
{

}

}
}