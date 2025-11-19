#include "GameController.h"
#include "WindowController.h"
#include "ToolWindow.h"
#include "Fonts.h"

GameController::GameController()
{
	m_shaderColor = {};
	m_shaderDiffuse = {};
	m_shaderFont = { };
	m_camera = {};
	m_meshBoxes.clear();
}

void GameController::Initialize()
{
	GLFWwindow* window = WindowController::GetInstance().GetWindow();
	M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW.");
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);;
	srand((unsigned int)time(0));

	m_camera = Camera(WindowController::GetInstance().GetResolution());
}

void GameController::RunGame()
{
	m_shaderColor = Shader();
	m_shaderColor.LoadShaders("Color.vertexshader", "Color.fragmentshader");

	m_shaderDiffuse = Shader();
	m_shaderDiffuse.LoadShaders("Diffuse.vertexshader", "Diffuse.fragmentshader");

	m_shaderSkybox = Shader();
	m_shaderSkybox.LoadShaders("Skybox.vertexshader", "Skybox.fragmentshader");

	m_shaderFont = Shader();
	m_shaderFont.LoadShaders("Font.vertexshader", "Font.fragmentshader");

	Mesh m = Mesh();
	m.Create(&m_shaderColor, "../Assets/Models/Teapot.obj");
	m.SetPosition({ 1.5f, 0.0f, 0.0f });
	m.SetColor({ 1.0f, 1.0f, 1.0f });
	m.SetScale({ 0.01f, 0.01f, 0.01f });
	Mesh::Lights.push_back(m);

	
	Mesh box = Mesh();
	box.Create(&m_shaderDiffuse, "../Assets/Models/OtherBox.obj");
	box.SetCameraPosition(m_camera.GetPosition());
	box.SetScale({ 0.25f, 0.25f, 0.25f });
	box.SetPosition({ 0.0f,1.0f,1.0f });
	m_meshBoxes.push_back(box);

	Mesh wall = Mesh();
	wall.Create(&m_shaderDiffuse, "../Assets/Models/Wall.obj");
	wall.SetCameraPosition(m_camera.GetPosition());
	wall.SetScale({ 0.05f, 0.05f, 0.05f });
	wall.SetPosition({ 0.0f, 0.0f, 0.0f });
	m_meshBoxes.push_back(wall);

	Fonts f = Fonts();
	f.Create(&m_shaderFont, "arial.ttf", 100);

	do
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_camera.Rotate();
		glm::mat4 view = glm::mat4(glm::mat3(m_camera.GetView()));

		for (unsigned int count = 0; count < m_meshBoxes.size(); count++)
		{
			m_meshBoxes[count].Render(m_camera.GetProjection() * m_camera.GetView());
		}

		for(unsigned int count = 0; count < Mesh::Lights.size(); count++)
		{
			Mesh::Lights[count].Render(m_camera.GetProjection() * m_camera.GetView());
		}

		glfwSwapBuffers(WindowController::GetInstance().GetWindow());
		glfwPollEvents();
	} 
	while (glfwGetKey(WindowController::GetInstance().GetWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(WindowController::GetInstance().GetWindow()) == 0);

	for(int count = 0; count <m_meshBoxes.size(); count++)
	{
		m_meshBoxes[count].Cleanup();
	}
	for (int count = 0; count < Mesh::Lights.size(); count++)
	{
		Mesh::Lights[count].Cleanup();
	};

	m_shaderDiffuse.Cleanup();
	m_shaderColor.Cleanup();
	m_shaderSkybox.Cleanup();
}

