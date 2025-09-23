#ifndef MESH_H
#define MESH_H

#include "StandardIncludes.h"
class Shader;
	
class Mesh
{
public:
	Mesh();
	virtual ~Mesh();

	void Create(Shader* _shader);
	void Cleanup();
	void Render(glm::mat4 _wvp);

private:
	Shader* m_shader;
	GLuint m_vertexBuffer;
	vector<GLfloat> m_vertexData;
	glm::mat4 m_world;
};

#endif

