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
	glEnable(GL_CULL_FACE);
	m_transform_system = Engine::Instance().GetTransformSystem();

	// TODO : This shoud be related to entity
	CurrentShader = Engine::Instance().GetResourceManager()->GetShaderProgram("testShader");


	glGenVertexArrays(1, &vao);

}

void EditorRender::Uninitialize()
{

}

static Vec3f m_cameraPosition{ 0.0f, 0.0f, 5.0f };
static Vec3f m_cameraTarget{ 0.0f, 0.0f, 1.0f };
void EditorRender::Update(SEfloat deltaTime)
{
	Keyboard m_keyboard;
	Mouse m_mouse;

	if (m_mouse.GetState(MouseState::Middle_Button) && m_keyboard.GetState(KeyboardState::A))
	{
		m_cameraPosition.x -= 0.05f;
		m_cameraTarget.x -= 0.05f;
	}
	if (m_mouse.GetState(MouseState::Middle_Button) && m_keyboard.GetState(KeyboardState::D))
	{
		m_cameraPosition.x += 0.05f;
		m_cameraTarget.x += 0.05f;
	}
	if (m_mouse.GetState(MouseState::Middle_Button) && m_keyboard.GetState(KeyboardState::W))
	{
		m_cameraPosition.y += 0.05f;
		m_cameraTarget.y += 0.05f;
	}
	if (m_mouse.GetState(MouseState::Middle_Button) && m_keyboard.GetState(KeyboardState::S))
	{
		m_cameraPosition.y -= 0.05f;
		m_cameraTarget.y -= 0.05f;
	}
	if (m_mouse.GetState(MouseState::Middle_Button) && m_keyboard.GetState(KeyboardState::Q))
	{
		m_cameraPosition.z += 0.05f;
	}
	if (m_mouse.GetState(MouseState::Middle_Button) && m_keyboard.GetState(KeyboardState::E))
	{
		m_cameraPosition.z -= 0.05f;
	}

	std::cout.precision(3);
	std::cout << "CamPos: " << m_cameraPosition.x << " -- " << m_cameraPosition.y << " -- " << m_cameraPosition.z << std::endl;

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

	//Uniform locations
	SEuint model_m_loc = glGetUniformLocation(shader, "model");
	SEuint view_m_loc = glGetUniformLocation(shader, "view");
	SEuint persp_m_loc = glGetUniformLocation(shader, "persp");


	//Mat4f persp = glm::ortho(0.f, (SEfloat)gui::_gui_width, 0.f, (SEfloat)gui::_gui_heigth,0.01f, 100.0f);
	Mat4f persp = glm::perspectiveFov(glm::radians(45.f), 1200.f, 800.f, 0.1f, 100.f);
	glUniformMatrix4fv
	(
		persp_m_loc,
		1,
		GL_FALSE,
		&persp[0][0]
	);

	//Mat4f view = Engine::Instance().GetCamera()->GetCameraView();
	//Mat4f view = glm::lookAt(Vec3f(0.0f, 0.0f, -10.0f), Vec3f(0.0f), Vec3f(0.0f, 1.0f, 0.0f));
	Mat4f view = glm::lookAt(m_cameraPosition, Vec3f(m_cameraPosition.x, m_cameraPosition.y, 0.0f), Vec3f(0.0f, 1.0f, 0.0f));
	//Mat4f view = glm::lookAt(m_cameraPosition, Vec3f(0.0f), Vec3f(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv
	(
		view_m_loc,
		1,
		GL_FALSE,
		&view[0][0]
	);

	glBindVertexArray(vao);

	for (auto entity : Engine::Instance().GetEntityMgr()->GetEntities())
	{

		if (entity.second.components.count(COMPONENT_TYPE::SHAPE))
		{
			auto& shape_comp = m_transform_system->m_cShapes.at(entity.second.components.at(COMPONENT_TYPE::SHAPE));
			SEuint pos_buffer;
			glGenBuffers(1, &pos_buffer);
			glBindBuffer(GL_ARRAY_BUFFER, pos_buffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(shape_comp.points.at(0)) * shape_comp.points.size(), shape_comp.points.data(), GL_DYNAMIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(shape_comp.points.at(0)), 0);

			glBindBuffer(GL_ARRAY_BUFFER, 0);

			//glEnableVertexAttribArray(0);
			//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(shape_comp.points.at(0)), &shape_comp.points.at(0));

			if (entity.second.components.count(COMPONENT_TYPE::TEXTURE))
			{
				auto i = GetTextureComponent(entity.second.components.at(COMPONENT_TYPE::TEXTURE))->handle;
				if (i != -1)
				{
					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, GetTextureComponent(entity.second.components.at(COMPONENT_TYPE::TEXTURE))->handle);

					glUniform1i(textureLocation, 0);

					glEnableVertexAttribArray(2);
					glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(SEfloat) * 2, &texCoords[0]);
				}
			}

			auto pos = TransformSystem::TransformableComponents.at(shape_comp.ownerID).position;

			//Mat4f model = TransformSystem::TransformableComponents.at(shape_comp.ownerID).modelMatrix;
			Mat4f model = glm::translate(Mat4f(1.0f), TransformSystem::TransformableComponents.at(shape_comp.ownerID).position);


			glUniformMatrix4fv
			(
				model_m_loc,
				1,
				GL_FALSE,
				&model[0][0]
			);

			glDrawElements(
				GL_TRIANGLES,
				shape_comp.indices.size(),
				GL_UNSIGNED_SHORT,
				shape_comp.indices.data()
			);

			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(2);
			glBindTexture(GL_TEXTURE_2D, 0);

			glDeleteBuffers(1, &pos_buffer);
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