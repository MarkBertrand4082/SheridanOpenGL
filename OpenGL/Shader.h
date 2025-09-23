#ifndef SHADER
#define SHADER

#include "StandardIncludes.h"

class Shader
{
public:
	Shader();
	virtual ~Shader() {}

	GLuint GetProgramID() { return m_programID; }
	GLuint GetAttrVertices() { return m_attrVertices; }
	GLuint GetAttrColors() { return m_attrColors; }
	GLuint GetAttrWVP() { return m_attrWVP; }


	void LoadShaders(const char* _vertexFilePath, const char* _fragmentFilePath);
	void Cleanup();

private:
	void CreateShaderProgram(const char* _vertexFilePath, const char* _fragmentFilePath);
	GLuint LoadShaderFile(const char* _filePath, GLenum _type);
	void LoadAttributes();
	void EvaluateShader(int _infoLength, GLuint _id);

	GLuint m_programID;
	GLuint m_attrVertices;
	GLint m_result = GL_FALSE;
	GLuint m_attrWVP;
	GLuint m_attrColors;
	int m_infoLogLength;
};
#endif
