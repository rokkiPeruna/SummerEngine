#include <core/EditorRender.h>
#include <systems/AnimationSystem.h>
#include <systems/TransformSystem.h>


namespace se
{
namespace priv
{

EditorRender::EditorRender(Engine& engine_ref)
	: Render(engine_ref)
	, m_dyn_rend_batches{}
	, m_batch_value_map{}
	, CurrentShader(nullptr)
{
	m_dyn_rend_batches.reserve(1000);
}

EditorRender::~EditorRender()
{

}

namespace
{
static SEuint vao;
}

void EditorRender::Initialize()
{
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);

	// TODO : This shoud be related to entity
	CurrentShader = m_engine.GetResourceManager().GetShaderProgram("testShader");

	SEuint shader = CurrentShader->GetShaderID();

	//Binds attribs to const positions
	glBindAttribLocation(shader, static_cast<SEuint>(SHADER_ATTRIB_INDEX::POSITION), "vertexPosition");
	glBindAttribLocation(shader, static_cast<SEuint>(SHADER_ATTRIB_INDEX::COLOR), "vertexColor");
	glBindAttribLocation(shader, static_cast<SEuint>(SHADER_ATTRIB_INDEX::TEX_COORDS), "vertexTexture");
}

void EditorRender::Uninitialize()
{

}

SEfloat texCoords[] = {
	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f
};

void EditorRender::Update(SEfloat)
{
	auto shader = CurrentShader->GetShaderID();
	glUseProgram(shader);
	SEuint textureLocation = glGetUniformLocation(shader, "fragment_texture");
	//SEuint transformLocation = glGetUniformLocation(shader, "transform");

	//Uniform locations
	SEuint model_m_loc = glGetUniformLocation(shader, "model");
	SEuint view_m_loc = glGetUniformLocation(shader, "view");
	SEuint persp_m_loc = glGetUniformLocation(shader, "persp");

	Mat4f persp = glm::perspective(glm::radians(45.f), (SEfloat)gui::_gui_width / (SEfloat)gui::_gui_heigth, 0.1f, 100.f);
	glUniformMatrix4fv
	(
		persp_m_loc,
		1,
		GL_FALSE,
		&persp[0][0]
	);

	Mat4f view = m_engine.GetCamera()->GetCameraView();
	glUniformMatrix4fv
	(
		view_m_loc,
		1,
		GL_FALSE,
		&view[0][0]
	);

	for (auto& b : m_dyn_rend_batches)
	{
		glBindVertexArray(b.vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, b.ind_buffer);

		if (b.texco_buffer != -1)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, b.texture_handle);
			glUniform1i(textureLocation, 0);
		}

		for (auto& e_id : b.entity_ids)
		{
			Mat4f model = TransformSystem::TransformableComponents.at(e_id).modelMatrix;
			glUniformMatrix4fv
			(
				model_m_loc,
				1,
				GL_FALSE,
				&model[0][0]
			);
			glDrawElements(
				GL_TRIANGLES,
				b.num_indices,
				GL_UNSIGNED_SHORT,
				0
			);
		}
	}
	glUseProgram(0);
}

void EditorRender::OnEntityAdded(const Entity& entity)
{
	//If no shape, no need to draw
	if (!entity.components.count(COMPONENT_TYPE::SHAPE))
		return;

	//If we have shape, we can at least draw it as black
	auto shape = GetShapeComponent(entity.components.at(COMPONENT_TYPE::SHAPE));

	SEuint tex_handle = SEuint_max;
	if (entity.components.count(COMPONENT_TYPE::TEXTURE))
	{
		tex_handle = GetTextureComponent(entity.components.at(COMPONENT_TYPE::TEXTURE))->handle;
	}

	//Then we check if there is batch that matches our needs
	if (m_batch_value_map.count(Vec3u(shape->indices.size(), tex_handle, shape->points.size())))
	{
		m_batch_value_map.at(Vec3u(shape->indices.size(), tex_handle, shape->points.size()))->entity_ids.emplace_back(entity.id);
		return;
	}

	//If there is no approriate batch, create one
	m_dyn_rend_batches.emplace_back(DynRenderBatch(static_cast<SEuint>(shape->indices.size())));
	auto& b = m_dyn_rend_batches.back();
	b.entity_ids.emplace_back(entity.id);

	//and add it also to m_batch_values_map
	m_batch_value_map.emplace(Vec3u(
		shape->indices.size(),
		tex_handle,
		shape->points.size()),
		&b
	);

	//Vertex positions
	b.CreateBuffer(b.pos_buffer, static_cast<SEuint>(shape->points.size()) * sizeof(shape->points.at(0)), shape->points.data());
	b.BindAttribPtr(SHADER_ATTRIB_INDEX::POSITION, 3);

	//Indices
	b.CreateBuffer(b.ind_buffer, static_cast<SEuint>(shape->indices.size()) * sizeof(shape->indices.at(0)), shape->indices.data(), true);
	b.BindAttribPtr(SHADER_ATTRIB_INDEX::INDICES, 1);

	//Check for texture component
	if (entity.components.count(COMPONENT_TYPE::TEXTURE))
	{
		auto tex = GetTextureComponent(entity.components.at(COMPONENT_TYPE::TEXTURE));

		b.CreateBuffer(b.texco_buffer, sizeof(texCoords[0]) * 8, texCoords);
		b.BindAttribPtr(SHADER_ATTRIB_INDEX::TEX_COORDS, 2);
		b.texture_handle = tex->handle;
	}
}


void EditorRender::OnRendableComponentChanged(const Entity& entity)
{
	//If we add renable component we have to make sure that it is deleted from the former location

	if (!entity.components.count(COMPONENT_TYPE::SHAPE))
		return;

	auto shape = GetShapeComponent(entity.components.at(COMPONENT_TYPE::SHAPE));

	SEuint tex_handle = SEuint_max;
	if (entity.components.count(COMPONENT_TYPE::TEXTURE))
	{
		tex_handle = GetTextureComponent(entity.components.at(COMPONENT_TYPE::TEXTURE))->handle;
	}

	if(m_batch_value_map.count(Vec3u(shape->indices.size(), tex_handle, shape->points.size())))
	{
		auto& temp = m_batch_value_map.at(Vec3u(shape->indices.size(), tex_handle, shape->points.size()))->entity_ids;
		for (SEint i = 0; i < temp.size(); ++i)
		{
			if (entity.id == static_cast<SEuint>(temp.at(i))) 
			{
				temp.erase(temp.begin() + i);
				break;
			}
		}
	}
}

}// !namespace priv
}// !namespace se