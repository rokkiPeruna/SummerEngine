#include <renderers/EditorRender.h>
#include <systems/AnimationSystem.h>
#include <systems/TransformSystem.h>

#include <managers/EntityManager.h>
#include <managers/SceneManager.h> //For tiles

namespace se
{
namespace priv
{

EditorRender::EditorRender(Engine& engine_ref)
	: Render(engine_ref)
	, m_dyn_rend_batches{}
	, m_batch_value_map{}
	, CurrentShader(nullptr)
	, m_tile_buffers{}
	, m_tile_vao{ SEuint_max }
	, m_tile_z_offset{ 0.1f }
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

	glGenVertexArrays(1, &m_tile_vao);
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

	//Render tiles. Own shader for them, batching?? World is full of questions..
	_renderTiles(textureLocation, model_m_loc);

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

void EditorRender::_renderTiles(SEuint texture_location, SEuint model_loc)
{
	auto scene = m_engine.GetSceneMgr().GetCurrentScene();
	if (!scene || scene->GetTiles().empty())
		return;

	const auto& tiles = scene->GetTiles();

	//Create rects and tex coords from tiles 
	std::vector<Vec3f> rects{};
	rects.reserve(tiles.size() * 4);
	std::vector<Vec2f> tex_coords{};
	tex_coords.reserve(tiles.size() * 4);

	//Create vertices and tex coords
	_createRectAndTexCoordsFromTile(tiles, rects, tex_coords);

	//Create indices
	std::vector<SEuint> indices{};
	_createIndices(indices, tiles.size());


	glBindVertexArray(m_tile_vao);

	SEuint index_buf = _createBuffers(rects, tex_coords, indices);

	Mat4f model(1.0f);
	glUniformMatrix4fv
	(
		model_loc,
		1,
		GL_FALSE,
		&model[0][0]
	);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tiles.at(0).tex_handle);
	glUniform1i(texture_location, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buf);

	glDrawElements(
		GL_TRIANGLES,
		indices.size(),
		GL_UNSIGNED_INT,
		0
	);

	glDeleteBuffers(3, m_tile_buffers);
}

void EditorRender::_createRectAndTexCoordsFromTile(const std::vector<Tile>& tiles, std::vector<Vec3f>& vertices, std::vector<Vec2f>& tex_coords)
{
	auto pixels_per_unit = m_engine.GetPixelsPerOneUnit();
	SEfloat half_w = (tiles.at(0).w * 0.5f) / pixels_per_unit;
	SEfloat half_h = (tiles.at(0).h * 0.5f) / pixels_per_unit;

	for (const auto& tile : tiles)
	{
		//Vertices
		vertices.emplace_back(Vec3f(tile.position.x - half_w, tile.position.y - half_h, m_tile_z_offset)); //First (left-down)
		vertices.emplace_back(Vec3f(tile.position.x + half_w, tile.position.y - half_h, m_tile_z_offset)); //Second (rigth-down)
		vertices.emplace_back(Vec3f(tile.position.x + half_w, tile.position.y + half_h, m_tile_z_offset)); //Third (rigth-up)
		vertices.emplace_back(Vec3f(tile.position.x - half_w, tile.position.y + half_h, m_tile_z_offset)); //Fourth (left-up)

		//Tex coords
		const auto& tc = tile.norm_tex_coords;
		tex_coords.emplace_back(Vec2f(tc.x, tc.w)); //Fourth (left-up)
		tex_coords.emplace_back(Vec2f(tc.z, tc.w)); //Third (rigth-up)
		tex_coords.emplace_back(Vec2f(tc.z, tc.y)); //Second (rigth-down)
		tex_coords.emplace_back(Vec2f(tc.x, tc.y)); //First (left-down)
	}
}

inline void EditorRender::_createIndices(std::vector<SEuint>& indices, SEuint num_of_tiles)
{
	SEint indice_adder = 0;
	for (SEuint i = 0; i < num_of_tiles; ++i, indice_adder += 4)
	{
		indices.emplace_back(0 + indice_adder);
		indices.emplace_back(1 + indice_adder);
		indices.emplace_back(2 + indice_adder);
		indices.emplace_back(0 + indice_adder);
		indices.emplace_back(2 + indice_adder);
		indices.emplace_back(3 + indice_adder);
	}
}

inline SEuint EditorRender::_createBuffers(std::vector<Vec3f>& vertices, std::vector<Vec2f>& tex_coords, std::vector<SEuint>& indices)
{
	//Generate buffers
	SEuint pos_buf = SEuint_max;
	SEuint texcoord_buf = SEuint_max;
	SEuint index_buf = SEuint_max;
	glGenBuffers(3, m_tile_buffers);
	pos_buf = m_tile_buffers[0];
	texcoord_buf = m_tile_buffers[1];
	index_buf = m_tile_buffers[2];

	glBindBuffer(GL_ARRAY_BUFFER, pos_buf);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices.at(0)) * vertices.size(), vertices.data(), GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(static_cast<SEuint>(SHADER_ATTRIB_INDEX::POSITION));
	glVertexAttribPointer(static_cast<SEuint>(SHADER_ATTRIB_INDEX::POSITION), 3, GL_FLOAT, GL_FALSE, 3 * sizeof(SEfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, texcoord_buf);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tex_coords.at(0)) * tex_coords.size(), tex_coords.data(), GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(static_cast<SEuint>(SHADER_ATTRIB_INDEX::TEX_COORDS));
	glVertexAttribPointer(static_cast<SEuint>(SHADER_ATTRIB_INDEX::TEX_COORDS), 2, GL_FLOAT, GL_FALSE, 2 * sizeof(SEfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buf);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices.at(0)) * indices.size(), indices.data(), GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return index_buf;
}

}// !namespace priv
}// !namespace se