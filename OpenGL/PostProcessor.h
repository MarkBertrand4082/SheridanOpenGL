#ifndef POST_PROCESSOR_H
#define POST_PROCESSOR_H

#include "StandardIncludes.h"
#include "Texture.h"

class Shader;

class PostProcessor
{
public:
	PostProcessor();
	virtual ~PostProcessor();

	void Create(Shader* _postShader);
	void Cleanup();
	void Start();
	void End();

private:
	GLuint m_frameBuffer;
	GLuint m_textureColorBuffer;
	GLuint m_renderBufferObject;
	GLuint m_vertexBuffer; //GPU
	Shader* m_postShader;

	void CreateVertices();
	void CreateBuffers();
	void BindVertices();
};

#endif