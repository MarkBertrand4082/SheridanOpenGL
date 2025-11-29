#ifndef MESH_H
#define MESH_H

#include "StandardIncludes.h"
#include "Texture.h"
#include "OBJ_Loader.h"

class Shader;
	
class Mesh
{
public:
	Mesh();
	virtual ~Mesh();

	void SetPosition(glm::vec3 _position) { m_position = _position; }
	glm::vec3 GetPosition() { return m_position; }
	void SetScale(glm::vec3 _scale) { m_scale = _scale; }
	void SetColor(glm::vec3 _color) { m_color = _color; }
	glm::vec3 GetColor() { return m_color; }
	void SetCameraPosition(glm::vec3 _cameraPosition) { m_cameraPosition = _cameraPosition; }

	void Create(Shader* _shader, string _file, int _instanceCount = 1);
	void Cleanup();
	void CalculateTransform();
	void Render(glm::mat4 _pv);

	static vector<Mesh> Lights;
	
private:

	void SetShaderVariables(glm::mat4 _pv);
	void BindAttributes();
	string Concat(string _s1, int _index, string _s2);
	string RemoveFolder(string _map);
	void CalculateTangents(vector<objl::Vertex> _vertices, objl::Vector3& _tangent, objl::Vector3& _bitangent);

	Shader* m_shader;
	Texture m_textureDiffuse;
	Texture m_textureSpecular;
	Texture m_textureNormal;
	GLuint m_vertexBuffer;//GPU buffer
	GLuint m_indexBuffer;//GPU buffer
	GLuint m_instanceBuffer;//GPU buffer
	vector<GLfloat> m_vertexData;//stored in RAM
	vector<GLubyte> m_indexData;//RAM
	vector<GLfloat> m_instanceData;//RAM
	bool m_enableNormalMap;
	int m_instanceCount;
	bool m_enableInstancing;
	int m_elementSize;

	//Transform
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
	glm::mat4 m_world;
	glm::vec3 m_color;
	glm::vec3 m_cameraPosition;
};

#endif

