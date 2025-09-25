#include "GameController.h"
#include "WindowController.h"
#include "ToolWindow.h"

GameController::GameController()
{
	m_shader = {};
	m_camera = {};
	m_mesh = {};
}

void GameController::Initialize()
{
	GLFWwindow* window = WindowController::GetInstance().GetWindow();
	M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW.");
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_CULL_FACE);

	m_camera = Camera(WindowController::GetInstance().GetResolution());
}

void GameController::RunGame()
{
	m_shader = Shader();
	m_shader.LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

	m_mesh = Mesh();
	m_mesh.Create(&m_shader);

	GLFWwindow* win = WindowController::GetInstance().GetWindow();
	do
	{
		glClear(GL_COLOR_BUFFER_BIT);
		m_mesh.Render(m_camera.GetProjection() * m_camera.GetView());
		glfwSwapBuffers(win);
		glfwPollEvents();
	} 
	while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(win) == 0);
	m_mesh.Cleanup();
	m_shader.Cleanup();
}

