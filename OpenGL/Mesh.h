#ifndef MESH_H
#define MESH_H

#include "StandardIncludes.h"
#include "Texture.h"

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
	Texture m_texture;
	Texture m_texture2;
	GLuint m_vertexBuffer;
	GLuint m_indexBuffer;
	vector<GLfloat> m_vertexData;
	vector<GLubyte> m_indexData;
	glm::mat4 m_world;
	glm::vec3 m_position;
	glm::vec3 m_rotation;
};

#endif

