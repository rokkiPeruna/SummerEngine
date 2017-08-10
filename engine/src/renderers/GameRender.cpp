#include <renderers/GameRender.h>
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

void GameRender::Update(SEfloat)
{
	auto shader = CurrentShader->GetShaderID();

	glUseProgram(shader);
	SEuint textureLocation = glGetUniformLocation(shader, "fragment_texture");

	//Uniform locations
	SEuint model_m_loc = glGetUniformLocation(shader, "model");
	SEuint view_m_loc = glGetUniformLocation(shader, "view");
	SEuint persp_m_loc = glGetUniformLocation(shader, "persp");

	Mat4f persp = glm::perspective(glm::radians(45.f), (SEfloat)gui::window_data::width / (SEfloat)gui::window_data::heigth, 0.1f, 100.f);
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

		if (b.texco_buffer != SEuint_max)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, b.texture_handle);
			glUniform1i(textureLocation, 0);
		}


		glDrawElements(
			GL_TRIANGLES,
			static_cast<SEuint>(b.indice_container.size()),
			GL_UNSIGNED_SHORT,
			0);

	}

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
			auto& entities = m_engine.GetEntityMgr().GetEntities();
			if (entities.at(e_id).components.count(COMPONENT_TYPE::TEXTURE))
			{
				auto tex = GetTextureComponent(entities.at(e_id).components.at(COMPONENT_TYPE::TEXTURE));
				SEint width = (tex->width) ? tex->width : tex->parent_img_w;
				SEint heigth = (tex->heigth) ? tex->heigth : tex->parent_img_h;
		
				Vec2f first(static_cast<SEfloat>(tex->x) / tex->parent_img_w, static_cast<SEfloat>((tex->y + heigth)) / tex->parent_img_h);
				Vec2f sec(static_cast<SEfloat>((tex->x + width)) / tex->parent_img_w, static_cast<SEfloat>((tex->y + heigth)) / tex->parent_img_h);
				Vec2f third(static_cast<SEfloat>((tex->x + width)) / tex->parent_img_w, static_cast<SEfloat>(tex->y) / tex->parent_img_h);
				Vec2f fourth(static_cast<SEfloat>(tex->x) / tex->parent_img_w, static_cast<SEfloat>(tex->y) / tex->parent_img_h);
		
				tex_coords[0] = fourth.x;
				tex_coords[1] = fourth.y;
				tex_coords[2] = third.x;
				tex_coords[3] = third.y;
				tex_coords[4] = sec.x;
				tex_coords[5] = sec.y;
				tex_coords[6] = first.x;
				tex_coords[7] = first.y;
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

void GameRender::OnEntityAdded(const Entity& entity)
{
	//Since we are here we know that this entity has shape
	//and that it can be drawn we can store it (shape)
	auto shape = GetShapeComponent(entity.components.at(COMPONENT_TYPE::SHAPE));

	//And if it has texture or not
	auto tex_handle = SEuint_max;
	if (entity.components.count(COMPONENT_TYPE::TEXTURE))
	{
		tex_handle = GetTextureComponent(entity.components.at(COMPONENT_TYPE::TEXTURE))->handle;
	}

	//Next we need to determine if it is dynamic or static
	if (entity.components.count(COMPONENT_TYPE::DYNAMIC))
	{
		//If the entity is dynamic we have to see throug dynamic batches if there is one 
		//with similar values

		if (m_batch_values_map_dynamic.count(batch_values(shape->indices.size(), tex_handle, shape->points.size())))
		{
			//If we have a similar batch we can add this new value to it
			m_batch_values_map_dynamic.at(batch_values(shape->indices.size(), tex_handle, shape->points.size()))->entity_ids.emplace_back(entity.id);
			return;
		}

		//If there is no proper existing dynamic batch. Create one
		else
		{

			m_dyn_rend_batches.emplace_back(DynamicRenderBatch(static_cast<SEuint>(shape->indices.size())));
			auto& b = m_dyn_rend_batches.back();

			b.entity_ids.emplace_back(entity.id);

			//Add entity to dynamic batch values

			m_batch_values_map_dynamic.emplace(batch_values(
				shape->indices.size(),
				tex_handle,
				shape->points.size()),
				&b);

			//Create position buffer
			b.CreateBuffer(b.pos_buffer, static_cast<SEuint>(shape->points.size()) * sizeof(shape->points.at(0)), shape->points.data());
			//Create attribute pointer for position buffer
			b.BindAttribPtr(SHADER_ATTRIB_INDEX::POSITION, 3);

			//Create indice buffer
			b.CreateBuffer(b.ind_buffer, static_cast<SEuint>(shape->indices.size()) * sizeof(shape->indices.at(0)), shape->indices.data(), true);
			//Create attribute pointer for indice buffer (This part is vain for now but "just in case..")
			b.BindAttribPtr(SHADER_ATTRIB_INDEX::INDICES, 1);
	
			//Check for texture component
			if (entity.components.count(COMPONENT_TYPE::TEXTURE))
			{
				auto tex = GetTextureComponent(entity.components.at(COMPONENT_TYPE::TEXTURE));

				b.CreateBuffer(b.texco_buffer, sizeof(SEfloat) * 8, 0);
				b.BindAttribPtr(SHADER_ATTRIB_INDEX::TEX_COORDS, 2);
				b.texture_handle = tex->handle;
			}
		}
	}
	else
	{
		//Adding to static batch : Fist we need to find out if we already have this kind of batch
		if (m_batch_value_map_static.count(batch_values(shape->indices.size(), tex_handle, shape->points.size())))
		{

			//SE_TODO Make sure that this works with gameLoop

			//If we have found suitable batch we can push this component into it
			auto batch_ptr = m_batch_value_map_static.at(batch_values(shape->indices.size(), tex_handle, shape->points.size()));
			batch_ptr->entity_ids.emplace_back(entity.id);

			//Before pushing shape positions we need to translate them with model matrix
			_inserValues(*batch_ptr, entity);
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
			m_batch_value_map_static.emplace(batch_values(
				shape->indices.size(),
				tex_handle,
				shape->points.size()),
				&batch);

			//After the new batch has been created we have to insert values of the current entity into it
			_inserValues(batch, entity);
			return;
		}
	}
}

void GameRender::OnEntityRemoved(const Entity&)
{
	//SE_TODO: Add logic
}

void GameRender::ClearRenderBatches()
{
	m_stat_rend_batches.clear();
	m_dyn_rend_batches.clear();
}

void GameRender::OnRendableComponentChanged(const Entity&)
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


	//Check for texture component
	if (staticBatch.texture_handle != SEuint_max)
	{
		staticBatch.CreateBuffer(
			staticBatch.texco_buffer,
			sizeof(staticBatch.texture_coordinate_container.at(0)) * staticBatch.offset_size,
			staticBatch.texture_coordinate_container.data());

		staticBatch.BindAttribPtr(SHADER_ATTRIB_INDEX::TEX_COORDS, 2);
	}

}


void GameRender::_inserValues(StaticRenderBatch& staticBatch, const Entity& entity)
{
	auto transform = m_engine.GetTransformSystem().TransformableComponents.at(entity.id);
	auto shape = GetShapeComponent(entity.components.at(COMPONENT_TYPE::SHAPE));


	for (unsigned int i = 0; i < shape->points.size(); ++i)
	{
		Vec3f temp = transform.modelMatrix * Vec4f(shape->points.at(i), 1.0);

		//Add current components positions to this batches position container
		staticBatch.position_container.emplace_back(temp);
	}

	//Add current component indices to this batches indice conainer
	if (staticBatch.indice_container.size())
	{
		for (auto i : shape->indices)
		{
			staticBatch.indice_container.emplace_back(i + staticBatch.index_offset);
		}
		staticBatch.index_offset += staticBatch.offset_size;

		//batch.indice_container.insert(batch.indice_container.end() - 1, shape->indices.begin(), shape->indices.end());
	}
	else if (!staticBatch.indice_container.size())
	{
		auto val = std::max_element(shape->indices.begin(), shape->indices.end());
		staticBatch.offset_size = (*val) + 1;
		staticBatch.index_offset = (*val) + 1;
		staticBatch.indice_container.insert(staticBatch.indice_container.begin(), shape->indices.begin(), shape->indices.end());
	}
	//Make sure total indice size is updated
	staticBatch.num_indices = static_cast<SEuint>(staticBatch.indice_container.size());

	// See if this entity has texture
	if (entity.components.count(COMPONENT_TYPE::TEXTURE))
	{
		//if entity has texture we need to create texture coodrinate for it
		auto tex = GetTextureComponent(entity.components.at(COMPONENT_TYPE::TEXTURE));

		//Take handle to texture
		staticBatch.texture_handle = tex->handle;

		SEint width = (tex->width) ? tex->width : tex->parent_img_w;
		SEint heigth = (tex->heigth) ? tex->heigth : tex->parent_img_h;

		Vec2f first(static_cast<SEfloat>(tex->x) / tex->parent_img_w, static_cast<SEfloat>((tex->y + heigth)) / tex->parent_img_h);
		Vec2f sec(static_cast<SEfloat>((tex->x + width)) / tex->parent_img_w, static_cast<SEfloat>((tex->y + heigth)) / tex->parent_img_h);
		Vec2f third(static_cast<SEfloat>((tex->x + width)) / tex->parent_img_w, static_cast<SEfloat>(tex->y) / tex->parent_img_h);
		Vec2f fourth(static_cast<SEfloat>(tex->x) / tex->parent_img_w, static_cast<SEfloat>(tex->y) / tex->parent_img_h);

		staticBatch.texture_coordinate_container.emplace_back(fourth.x, fourth.y);
		staticBatch.texture_coordinate_container.emplace_back(third.x, third.y);
		staticBatch.texture_coordinate_container.emplace_back(sec.x, sec.y);
		staticBatch.texture_coordinate_container.emplace_back(first.x, first.y);

	}

	return;

}


}// !namespace priv

}// !namespace SE