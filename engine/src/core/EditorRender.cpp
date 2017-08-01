#include <core/EditorRender.h>
#include <core/Engine.h>
#include <systems/AnimationSystem.h>

namespace se
{
namespace priv
{

EditorRender::EditorRender()
	: m_transform_system(nullptr)
{

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
	m_transform_system = Engine::Instance().GetTransformSystem();

	// TODO : This shoud be related to entity
	CurrentShader = Engine::Instance().GetResourceManager()->GetShaderProgram("testShader");


	glGenVertexArrays(1, &vao);
}

void EditorRender::Uninitialize()
{

}

void EditorRender::Update(SEfloat deltaTime)
{
	SEfloat texCoords[] =
	{
		0.0f,0.0f,
		1.0f,0.0f,
		1.0f,1.0f,
		0.0f,1.0f
	};

	auto shader = CurrentShader->GetShaderID();
	glUseProgram(shader);
	SEuint textureLocation = glGetUniformLocation(shader, "fragment_texture");
	SEuint transformLocation = glGetUniformLocation(shader, "transform");
	glBindAttribLocation(shader, 0, "vertexPosition");
	glBindAttribLocation(shader, 2, "vertexTexture");

	glBindVertexArray(vao);
	for (auto entity : Engine::Instance().GetEntityMgr()->GetEntities())
	{

		if (entity.second.components.count(COMPONENT_TYPE::SHAPE))
		{
			auto& shape_comp = m_transform_system->m_cShapes.at(entity.second.components.at(COMPONENT_TYPE::SHAPE));

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, shape_comp.points.size(), GL_FLOAT, GL_FALSE, sizeof(shape_comp.points.at(0).x) * 3, &shape_comp.points.at(0).x);

			if (entity.second.components.count(COMPONENT_TYPE::TEXTURE))
			{
				auto i = GetTextureComponent(entity.second.components.at(COMPONENT_TYPE::TEXTURE))->handle;
				if (i != -1)
				{
					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, GetTextureComponent(entity.second.components.at(COMPONENT_TYPE::TEXTURE))->handle);

					glUniform1i(textureLocation, 0);

					glEnableVertexAttribArray(2);
					glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(SEfloat) * 2, &texCoords[0]);
				}
			}


			Mat4f mvp = glm::perspective(45.f, 1200.f / 800.f, 0.1f, 100.f) * Engine::Instance().GetCamera()->GetCameraView() * m_transform_system->TransformableComponents.at(shape_comp.my_Transform).modelMatrix;
			glUniformMatrix4fv(transformLocation, 1, GL_FALSE, &mvp[0][0]);

			glDrawElements(
				GL_TRIANGLES,
				shape_comp.indices.size(),
				GL_UNSIGNED_SHORT,
				shape_comp.indices.data()
			);

			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(2);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
	glUseProgram(0);
}

void EditorRender::AddRenderable(CShape* shape, const Entity& entity)
{

}

void EditorRender::RemoveRenderable()
{

}




}// !namespace priv


}// !namespace se