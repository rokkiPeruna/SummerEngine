#include <renderers/EditorRender.h>
#include <systems/AnimationSystem.h>
#include <systems/TransformSystem.h>

#include <managers/EntityManager.h>

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

namespace
{
static SEuint vao;
}

void EditorRender::Initialize()
{
	///Set various OpenGL settings
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);								///Draw only triangles that are facing the camera with order for vertices as counter-clockwise
	glEnable(GL_DEPTH_TEST);							///Enable depth buffer testing so that fragments that cannot be seen are not drawn
	//glDepthFunc(GL_LESS);								///Give desired depth testing function, in this case if fragment's Z is less than current Z, discard fragment
	glEnable(GL_BLEND);									///Enable blending so that use of alpha values in textures is possible
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	///Give desired blending function, in this case source color affects N% and destination color affects 1-N%

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
	//Flush all batches
	m_dyn_rend_batches.clear();
	m_batch_value_map.clear();
}

void EditorRender::Update(SEfloat)
{
	auto shader = CurrentShader->GetShaderID();

	//SE_TODO: REMOVE for testing tex coords
	auto entities = m_engine.GetEntityMgr().GetEntities();

	glUseProgram(shader);
	SEuint textureLocation = glGetUniformLocation(shader, "fragment_texture");
	//SEuint transformLocation = glGetUniformLocation(shader, "transform");

	//Uniform locations
	SEuint model_m_loc = glGetUniformLocation(shader, "model");
	SEuint view_m_loc = glGetUniformLocation(shader, "view");
	SEuint persp_m_loc = glGetUniformLocation(shader, "persp");

	glUniformMatrix4fv
	(
		persp_m_loc,
		1,
		GL_FALSE,
		&m_perps_matrix[0][0]
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

		if (b.texco_buffer != SEuint_max)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, b.texture_handle);
			glUniform1i(textureLocation, 0);
		}

		for (auto& e_id : b.entity_ids)
		{
			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!UGLY WAY FOR TEX COORDS
			SEfloat tex_coords[8];			 
			if (entities.at(e_id).components.count(COMPONENT_TYPE::TEXTURE))
			{
				auto tex = GetTextureComponent(entities.at(e_id).components.at(COMPONENT_TYPE::TEXTURE));
				SEint width = (tex->width) ? tex->width : tex->parent_img_w;
				SEint heigth = (tex->heigth) ? tex->heigth : tex->parent_img_h;

				Vec2f first(static_cast<SEfloat>(tex->x) / tex->parent_img_w, static_cast<SEfloat>((tex->y + heigth)) / tex->parent_img_h);
				Vec2f sec(static_cast<SEfloat>((tex->x + width)) / tex->parent_img_w, static_cast<SEfloat>((tex->y + heigth)) / tex->parent_img_h);
				Vec2f third(static_cast<SEfloat>((tex->x + width)) / tex->parent_img_w, static_cast<SEfloat>(tex->y) / tex->parent_img_h);
				Vec2f fourth(static_cast<SEfloat>(tex->x) / tex->parent_img_w, static_cast<SEfloat>(tex->y) / tex->parent_img_h);

				tex_coords[0] = first.x;
				tex_coords[1] = first.y;
				tex_coords[2] = sec.x;
				tex_coords[3] = sec.y;
				tex_coords[4] = third.x;
				tex_coords[5] = third.y;
				tex_coords[6] = fourth.x;
				tex_coords[7] = fourth.y;
			}
			else
			{
				tex_coords[0] = 0.0f;
				tex_coords[1] = 0.0f;
				tex_coords[2] = 1.0f;
				tex_coords[3] = 0.0f;
				tex_coords[4] = 1.0f;
				tex_coords[5] = 1.0f;
				tex_coords[6] = 0.0f;
				tex_coords[7] = 1.0f;
			}
			glBindBuffer(GL_ARRAY_BUFFER, b.texco_buffer);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(tex_coords), tex_coords);
			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!UGLY WAY FOR TEX COORDS ENDS

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
	m_dyn_rend_batches.emplace_back(DynamicRenderBatch(static_cast<SEuint>(shape->indices.size())));
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

		//b.CreateBuffer(b.texco_buffer, sizeof(texCoords[0]) * 8, texCoords);
		//b.BindAttribPtr(SHADER_ATTRIB_INDEX::TEX_COORDS, 2);
		b.CreateBuffer(b.texco_buffer, sizeof(SEfloat) * 8, 0);
		b.BindAttribPtr(SHADER_ATTRIB_INDEX::TEX_COORDS, 2);
		b.texture_handle = tex->handle;
	}
}

void EditorRender::OnEntityRemoved(const Entity& entity)
{
	//If no shape, it's not in any batch
	if (!entity.components.count(COMPONENT_TYPE::SHAPE))
		return;

	auto shape = GetShapeComponent(entity.components.at(COMPONENT_TYPE::SHAPE));

	SEuint tex_handle = SEuint_max;
	if (entity.components.count(COMPONENT_TYPE::TEXTURE))
	{
		tex_handle = GetTextureComponent(entity.components.at(COMPONENT_TYPE::TEXTURE))->handle;
	}

	auto & e_ids = m_batch_value_map.at(Vec3u(shape->indices.size(), tex_handle, shape->points.size()))->entity_ids;
	e_ids.erase(std::find(e_ids.begin(), e_ids.end(), entity.id));
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

	if (m_batch_value_map.count(Vec3u(shape->indices.size(), tex_handle, shape->points.size())))
	{
		auto& temp = m_batch_value_map.at(Vec3u(shape->indices.size(), tex_handle, shape->points.size()))->entity_ids;
		for (SEint i = 0; i < temp.size(); ++i)
		{
			if (entity.id == temp.at(i))
			{
				temp.erase(temp.begin() + i);
				break;
			}
		}
	}
}

void EditorRender::ClearRenderBatches()
{
	m_dyn_rend_batches.clear();
	m_batch_value_map.clear();
}
}// !namespace priv
}// !namespace se