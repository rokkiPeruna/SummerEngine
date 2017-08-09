#include <core/GameRender.h>
#include <systems/AnimationSystem.h>
#include <systems/TransformSystem.h>

#include <managers/EntityManager.h>

namespace se
{

namespace priv
{

GameRender::GameRender(Engine& engine_ref)
	: Render(engine_ref)
	, CurrentShader(nullptr)
{
	m_stat_rend_batches.reserve(1000);
}


GameRender::~GameRender()
{

}

void GameRender::Initialize()
{
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);


	CurrentShader = m_engine.GetResourceManager().GetShaderProgram("testShader");
	SEuint shader = CurrentShader->GetShaderID();


	glBindAttribLocation(shader, static_cast<SEuint>(SHADER_ATTRIB_INDEX::POSITION), "vertexPosition");
	glBindAttribLocation(shader, static_cast<SEuint>(SHADER_ATTRIB_INDEX::COLOR), "vertexColor");
	glBindAttribLocation(shader, static_cast<SEuint>(SHADER_ATTRIB_INDEX::TEX_COORDS), "vertexTexture");


	//Fist Create static buffers from existing static objects
	for (auto i : m_engine.GetEntityMgr().GetEntities())
	{
		//If entity has no shape we don't need to draw it
		if (i.second.components.count(COMPONENT_TYPE::SHAPE))
		{
			OnEntityAdded(i.second);
		}
	}

	//After initialization of static entities is complete we can create static buffer objects
	for (auto& i : m_stat_rend_batches)
	{
		_createStaticBuffers(i);
	}

}

void GameRender::Uninitialize()
{

}

void GameRender::Update(SEfloat deltaTime)
{
	auto shader = CurrentShader->GetShaderID();

	glUseProgram(shader);
	SEuint textureLocation = glGetUniformLocation(shader, "fragment_texture");

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

	//static batches
	for (auto& b : m_stat_rend_batches)
	{
		glBindVertexArray(b.vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, b.ind_buffer);

		glDrawElements(GL_TRIANGLES, b.indice_container.size(), GL_UNSIGNED_SHORT, 0);

	}

	glUseProgram(0);

}

void GameRender::OnEntityAdded(const Entity& entity)
{
	//Since we are here we know that this entity has shape
	//and that it can be drawn we can store it (shape)
	auto shape = GetShapeComponent(entity.components.at(COMPONENT_TYPE::SHAPE));

	//And if it has texture or not
	auto tex_handle = SEfloat_max;
	if (entity.components.count(COMPONENT_TYPE::TEXTURE))
	{
		tex_handle = GetTextureComponent(entity.components.at(COMPONENT_TYPE::TEXTURE))->handle;
	}

	//Next we need to determine if it is dynamic or static
	if (entity.components.count(COMPONENT_TYPE::DYNAMIC))
	{
		// SE_TODO Add to dynamic Batch
	}
	else
	{
		//Adding to static batch : Fist we need to find out if we already have this kind of batch
		if (m_batch_value_map.count(Vec3u(shape->indices.size(), tex_handle, shape->points.size())))
		{

			//SE_TODO Make sure that this works with gameLoop

			//If we have found suitable batch we can push this component into it
			auto batch_ptr = m_batch_value_map.at(Vec3u(shape->indices.size(), tex_handle, shape->points.size()));
			batch_ptr->entity_ids.emplace_back(entity.id);

			//Before pushing shape positions we need to translate them with model matrix
			auto transform = m_engine.GetTransformSystem().TransformableComponents.at(entity.id);

			for (unsigned int i = 0; i < shape->points.size(); ++i)
			{
				Vec3f temp = transform.modelMatrix * Vec4f(shape->points.at(i), 1.0);

				//Add current components positions to this batches position container
				batch_ptr->position_container.emplace_back(temp);
			}

			//Add current component indices to this batches indice conainer
			for (auto i : shape->indices)
			{
				batch_ptr->indice_container.emplace_back(i + batch_ptr->index_offset);
			}
			batch_ptr->index_offset += batch_ptr->index_offset;
			//batch_ptr->indice_container.insert(batch_ptr->indice_container.end() - 1, shape->indices.begin(), shape->indices.end());

			//Make sure total indice size is updated
			batch_ptr->num_indices = batch_ptr->indice_container.size();

			//See if this entity has texture
			if (entity.components.count(COMPONENT_TYPE::TEXTURE))
			{
				//if entity has texture we need to create texture coodrinate for it
				auto tex = GetTextureComponent(entity.components.at(COMPONENT_TYPE::TEXTURE));

				SEint width = (tex->width) ? tex->width : tex->parent_img_w;
				SEint heigth = (tex->heigth) ? tex->heigth : tex->parent_img_h;

				Vec2f first(static_cast<SEfloat>(tex->x) / tex->parent_img_w, static_cast<SEfloat>((tex->y + heigth)) / tex->parent_img_h);
				Vec2f sec(static_cast<SEfloat>((tex->x + width)) / tex->parent_img_w, static_cast<SEfloat>((tex->y + heigth)) / tex->parent_img_h);
				Vec2f third(static_cast<SEfloat>((tex->x + width)) / tex->parent_img_w, static_cast<SEfloat>(tex->y) / tex->parent_img_h);
				Vec2f fourth(static_cast<SEfloat>(tex->x) / tex->parent_img_w, static_cast<SEfloat>(tex->y) / tex->parent_img_h);

				std::vector<Vec2f> tex_coords;

				// SE_TODO : See if this 'can be' tweaked a bit
				tex_coords.emplace_back(fourth.x, fourth.y);
				tex_coords.emplace_back(third.x, third.y);
				tex_coords.emplace_back(sec.x, sec.y);
				tex_coords.emplace_back(first.x, first.y);

				//After texture coordination creation we need to push it into conainer with similar coordinates
				batch_ptr->texture_coordinate_container.insert(
					batch_ptr->texture_coordinate_container.end() - 1,
					tex_coords.begin(),
					tex_coords.end());

			}

			return;
		}
		//If we don't have proper existing batch, we have to create one
		else
		{
			//Add new batch with minimum ammount of data
			m_stat_rend_batches.emplace_back(StaticRenderBatch(static_cast<SEuint>(shape->indices.size())));

			//'Select' this newly created batch and add current entity as its first parameter
			auto& batch = m_stat_rend_batches.back();
			batch.entity_ids.emplace_back(entity.id);

			//Add it to batch values so in future we can compare if there are similar objects
			m_batch_value_map.emplace(Vec3u(
				shape->indices.size(),
				tex_handle,
				shape->points.size()),
				&batch
			);

			//After the new batch has been created we have to insert values of the current entity into it

			auto transform = m_engine.GetTransformSystem().TransformableComponents.at(entity.id);

			for (unsigned int i = 0; i < shape->points.size(); ++i)
			{
				Vec3f temp = transform.modelMatrix * Vec4f(shape->points.at(i), 1.0);

				//Add current components positions to this batches position container
				batch.position_container.emplace_back(temp);
			}

			//Add current component indices to this batches indice conainer
			if (batch.indice_container.size())
			{	
				for (auto i : shape->indices)
				{
					batch.indice_container.emplace_back(i + batch.index_offset);
				}
				batch.index_offset += batch.index_offset;

				//batch.indice_container.insert(batch.indice_container.end() - 1, shape->indices.begin(), shape->indices.end());
			}
			else if (!batch.indice_container.size())
			{
				auto val = std::max_element(shape->indices.begin(), shape->indices.end());
				batch.index_offset = (*val) + 1;
				batch.indice_container.insert(batch.indice_container.begin(), shape->indices.begin(), shape->indices.end());
			}
			//Make sure total indice size is updated
			batch.num_indices = batch.indice_container.size();

			// See if this entity has texture
			if (entity.components.count(COMPONENT_TYPE::TEXTURE))
			{
				//if entity has texture we need to create texture coodrinate for it
				auto tex = GetTextureComponent(entity.components.at(COMPONENT_TYPE::TEXTURE));

				SEint width = (tex->width) ? tex->width : tex->parent_img_w;
				SEint heigth = (tex->heigth) ? tex->heigth : tex->parent_img_h;

				Vec2f first(static_cast<SEfloat>(tex->x) / tex->parent_img_w, static_cast<SEfloat>((tex->y + heigth)) / tex->parent_img_h);
				Vec2f sec(static_cast<SEfloat>((tex->x + width)) / tex->parent_img_w, static_cast<SEfloat>((tex->y + heigth)) / tex->parent_img_h);
				Vec2f third(static_cast<SEfloat>((tex->x + width)) / tex->parent_img_w, static_cast<SEfloat>(tex->y) / tex->parent_img_h);
				Vec2f fourth(static_cast<SEfloat>(tex->x) / tex->parent_img_w, static_cast<SEfloat>(tex->y) / tex->parent_img_h);

				std::vector<Vec2f> tex_coords;

				// SE_TODO : See if this 'can be' tweaked a bit
				tex_coords.emplace_back(fourth.x, fourth.y);
				tex_coords.emplace_back(third.x, third.y);
				tex_coords.emplace_back(sec.x, sec.y);
				tex_coords.emplace_back(first.x, first.y);

				//After texture coordination creation we need to push it into conainer with similar coordinates
				batch.texture_coordinate_container.insert(
					batch.texture_coordinate_container.end() - 1,
					tex_coords.begin(),
					tex_coords.end());

			}

			return;
		}
	}
}

void GameRender::OnRendableComponentChanged(const Entity& entity)
{

}

void GameRender::_createStaticBuffers(StaticRenderBatch& staticBatch)
{
	//Create position vertex buffer object
	staticBatch.CreateBuffer(
		staticBatch.pos_buffer,
		static_cast<SEuint>(staticBatch.position_container.size()
			* sizeof(staticBatch.position_container.at(0))),
		staticBatch.position_container.data());

	staticBatch.BindAttribPtr(SHADER_ATTRIB_INDEX::POSITION, 3);

	//Create indice vertex buffer object
	staticBatch.CreateBuffer(
		staticBatch.ind_buffer,
		static_cast<SEuint>(staticBatch.indice_container.size())
		* sizeof(staticBatch.indice_container.at(0)),
		staticBatch.indice_container.data(),
		true);

	staticBatch.BindAttribPtr(SHADER_ATTRIB_INDEX::INDICES, 1);
}



}// !namespace priv

}// !namespace SE