#include "GameController.h"
#include "WindowController.h"
#include "ToolWindow.h"
#include "Fonts.h"

GameController::GameController()
{
	m_shaderColor = {};
	m_shaderDiffuse = {};
	m_shaderFont = { };
	m_shaderLight = { };
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
	srand((unsigned int)time(0));

	m_camera = Camera(WindowController::GetInstance().GetResolution());
}

void GameController::RunGame()
{
	OpenGL::ToolWindow^ window = gcnew OpenGL::ToolWindow();
	window->Show();



	m_shaderColor = Shader();
	m_shaderColor.LoadShaders("Color.vertexshader", "Color.fragmentshader");
	m_shaderDiffuse = Shader();
	m_shaderDiffuse.LoadShaders("Diffuse.vertexshader", "Diffuse.fragmentshader");
	m_shaderFont = Shader();
	m_shaderFont.LoadShaders("Font.vertexshader", "Font.fragmentshader");
	m_shaderLight = Shader();
	m_shaderLight.LoadShaders("Light.vertexshader", "Light.fragmentshader");


	Mesh m = Mesh();
	m.Create(&m_shaderLight, "../Assets/Models/Sphere.obj");
	m.SetPosition({ 0.0f, 0.0f, -1.0f });
	m.SetColor({ 1.0f, 1.0f, 1.0f });
	m.SetScale({ 0.005f, 0.005f, 0.005f });
	Mesh::Lights.push_back(m);
	

	Mesh teapot = Mesh();
	teapot.Create(&m_shaderDiffuse, "../Assets/Models/Teapot2.obj");
	teapot.SetCameraPosition(m_camera.GetPosition());
	teapot.SetScale({ 0.02f, 0.02f, 0.02f });
	teapot.SetPosition({ 0.0f,0.0f,0.0f });
	m_meshBoxes.push_back(teapot);

	Fonts f = Fonts();
	f.Create(&m_shaderFont, "arial.ttf", 50);

	do
	{	
		System::Windows::Forms::Application::DoEvents();

		

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glGetError();

		for (unsigned int count = 0; count < m_meshBoxes.size(); count++)
		{
			m_meshBoxes[count].Render(m_camera.GetProjection() * m_camera.GetView());
		}
		if (OpenGL::ToolWindow::MoveLight) {
			for (unsigned int count = 0; count < Mesh::Lights.size(); count++)
			{
				Mesh::Lights[count].Render(m_camera.GetProjection() * m_camera.GetView());
				if (OpenGL::ToolWindow::resetLight) {
					Mesh::Lights[count].SetPosition(glm::vec3(0.0, 0.0, -1.0));
					OpenGL::ToolWindow::resetLight = false;
				}
			}
		}
		
		if (OpenGL::ToolWindow::resetPot) {
			m_meshBoxes[0].SetPosition(glm::vec3(0.0, 0.0, 0.0));
			OpenGL::ToolWindow::resetPot = false;
		}

		glm::vec3 colours = glm::vec3(OpenGL::ToolWindow::Red, OpenGL::ToolWindow::Green, OpenGL::ToolWindow::Blue);

		Mesh mesh;

		glUseProgram(m_shaderDiffuse.GetProgramID());
		GLint loc = glGetUniformLocation(m_shaderDiffuse.GetProgramID(), "byPosition");
		glUniform1f(loc, OpenGL::ToolWindow::ByPosition);
		if (OpenGL::ToolWindow::MoveLight) {
			GLint loc = glGetUniformLocation(m_shaderDiffuse.GetProgramID(), "red");
			glUniform1f(loc, colours.x);
			loc = glGetUniformLocation(m_shaderDiffuse.GetProgramID(), "green");
			glUniform1f(loc, colours.y);
			loc = glGetUniformLocation(m_shaderDiffuse.GetProgramID(), "blue");
			glUniform1f(loc, colours.z);
			loc = glGetUniformLocation(m_shaderDiffuse.GetProgramID(), "specStr");
			glUniform1f(loc, OpenGL::ToolWindow::Specular);

		}
		else if (OpenGL::ToolWindow::ByPosition) {
			//vec4(10 * vec3(abs(red), abs(green), abs(blue)), 1.0);
			GLint loc = glGetUniformLocation(m_shaderDiffuse.GetProgramID(), "red");
			glUniform1f(loc, mesh.GetPosition().x+1.0);
			loc = glGetUniformLocation(m_shaderDiffuse.GetProgramID(), "green");
			glUniform1f(loc, mesh.GetPosition().y+1.0);
			loc = glGetUniformLocation(m_shaderDiffuse.GetProgramID(), "blue");
			glUniform1f(loc, mesh.GetPosition().z+1.0);
		}
		

		double msX, msY;

		glfwGetCursorPos(WindowController::GetInstance().GetWindow(), &msX, &msY);
		//center points of quadrants
		float qHeight = ((float)WindowController::GetInstance().GetResolution().m_height / 4.0) / (float)WindowController::GetInstance().GetResolution().m_width;
		float qWidth = ((float)WindowController::GetInstance().GetResolution().m_width / 4.0) / (float)WindowController::GetInstance().GetResolution().m_width;
		glm::vec3 goal;

		//Should've just edited the code to move both the teapot and light with same code
		//but I just didn't

		if (glfwGetMouseButton(WindowController::GetInstance().GetWindow(),0) == GLFW_PRESS) {
			if (OpenGL::ToolWindow::MoveLight) {
				for (unsigned int count = 0; count < Mesh::Lights.size(); count++)
				{
					glm::vec3 pos = Mesh::Lights[count].GetPosition();
					//Top-Left
					if (msX < WindowController::GetInstance().GetResolution().m_width / 2 && msY < WindowController::GetInstance().GetResolution().m_height / 2)
					{
						goal = glm::vec3(0.5,0.5,-1);
						if (pos != goal)
						{
							glm::vec2 direction = glm::normalize(goal - pos);

							glm::vec3 translation = glm::vec3(pos.x+= (direction.x/1000.0),pos.y+=(direction.y/1000.0),-1.0);
							Mesh::Lights[count].SetPosition(translation);
						}


					}
					//Top-Right
					else if (msX > WindowController::GetInstance().GetResolution().m_width / 2 && msY < WindowController::GetInstance().GetResolution().m_height / 2)
					{
						goal = glm::vec3(-0.5, 0.5, -1);
						if (pos != goal)
						{
							glm::vec2 direction = glm::normalize(goal - pos);

							glm::vec3 translation = glm::vec3(pos.x += (direction.x / 1000.0), pos.y += (direction.y / 1000.0), -1.0);
							Mesh::Lights[count].SetPosition(translation);
						}


					}
					//Bottom-Left
					else if (msX < WindowController::GetInstance().GetResolution().m_width / 2 && msY > WindowController::GetInstance().GetResolution().m_height / 2)
					{
						goal = glm::vec3(0.5, -0.5, -1);
						if (pos != goal)
						{
							glm::vec2 direction = glm::normalize(goal - pos);

							glm::vec3 translation = glm::vec3(pos.x += (direction.x / 1000.0), pos.y += (direction.y / 1000.0), -1.0);
							Mesh::Lights[count].SetPosition(translation);
						}


					}
					//Bottom-Right
					else if (msX > WindowController::GetInstance().GetResolution().m_width / 2 && msY > WindowController::GetInstance().GetResolution().m_height / 2)
					{
						goal = glm::vec3(-0.5, -0.5, -1);
						if (pos != goal)
						{
							glm::vec2 direction = glm::normalize(goal - pos);

							glm::vec3 translation = glm::vec3(pos.x += (direction.x / 1000.0), pos.y += (direction.y / 1000.0), -1.0);
							Mesh::Lights[count].SetPosition(translation);
						}


					}
				
				}
			}
			if (OpenGL::ToolWindow::ByPosition) {
				for (unsigned int count = 0; count < Mesh::Lights.size(); count++)
				{
					glm::vec3 pos = m_meshBoxes[0].GetPosition();
					//Top-Left
					if (msX < WindowController::GetInstance().GetResolution().m_width / 2 && msY < WindowController::GetInstance().GetResolution().m_height / 2)
					{
						goal = glm::vec3(0.5, 0.5, -1);
						if (pos != goal)
						{
							glm::vec2 direction = glm::normalize(goal - pos);

							glm::vec3 translation = glm::vec3(pos.x += (direction.x / 100.0), pos.y += (direction.y / 100.0), -1.0);
							m_meshBoxes[0].SetPosition(translation);
						}


					}
					//Top-Right
					else if (msX > WindowController::GetInstance().GetResolution().m_width / 2 && msY < WindowController::GetInstance().GetResolution().m_height / 2)
					{
						goal = glm::vec3(-0.5, 0.5, -1);
						if (pos != goal)
						{
							glm::vec2 direction = glm::normalize(goal - pos);

							glm::vec3 translation = glm::vec3(pos.x += (direction.x / 100.0), pos.y += (direction.y / 100.0), 0.0);
							m_meshBoxes[0].SetPosition(translation);
						}


					}
					//Bottom-Left
					else if (msX < WindowController::GetInstance().GetResolution().m_width / 2 && msY > WindowController::GetInstance().GetResolution().m_height / 2)
					{
						goal = glm::vec3(0.5, -0.5, -1);
						if (pos != goal)
						{
							glm::vec2 direction = glm::normalize(goal - pos);

							glm::vec3 translation = glm::vec3(pos.x += (direction.x / 100.0), pos.y += (direction.y / 100.0), 0.0);
							m_meshBoxes[0].SetPosition(translation);
						}


					}
					//Bottom-Right
					else if (msX > WindowController::GetInstance().GetResolution().m_width / 2 && msY > WindowController::GetInstance().GetResolution().m_height / 2)
					{
						goal = glm::vec3(-0.5, -0.5, -1);
						if (pos != goal)
						{
							glm::vec2 direction = glm::normalize(goal - pos);

							glm::vec3 translation = glm::vec3(pos.x += (direction.x / 100.0), pos.y += (direction.y / 100.0), 0.0);
							m_meshBoxes[0].SetPosition(translation);
						}


					}

				}
			}
		}
		
		//f.RenderText("Mouse Position ("+to_string(msX) + ", " + to_string(msY) + ")", 10, 100, 0.5f, {1.0f, 1.0f, 0.0f});
		f.RenderText("Mouse Position ("+to_string(Mesh::Lights[0].GetPosition().x) + ", " + to_string(Mesh::Lights[0].GetPosition().y) + ")", 10, 100, 0.5f, {1.0f, 1.0f, 0.0f});
		glfwSwapBuffers(WindowController::GetInstance().GetWindow());
		glfwPollEvents();
	} 
	while (glfwGetKey(WindowController::GetInstance().GetWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(WindowController::GetInstance().GetWindow()) == 0);

	for(int count = 0; count <m_meshBoxes.size(); count++)
	{
		m_meshBoxes[count].Cleanup();
	}
	for(int count = 0; count <Mesh::Lights.size(); count++)
	{
		Mesh::Lights[count].Cleanup();
	}

	m_shaderDiffuse.Cleanup();
	m_shaderColor.Cleanup();
}

