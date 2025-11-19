#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "StandardIncludes.h"
#include "Shader.h"
#include "Mesh.h"
#include "Skybox.h"
#include "WindowController.h"
#include "Camera.h"

class GameController : public Singleton<GameController>
{
public:
	GameController();
	virtual ~GameController() {}

	void Initialize();
	void RunGame();

private:
	Shader m_shaderColor;
	Shader m_shaderDiffuse;
	Shader m_shaderFont;
	Shader m_shaderSkybox;
	Camera m_camera;
	vector<Mesh> m_meshBoxes;
	Skybox m_skybox;
};

#endif

