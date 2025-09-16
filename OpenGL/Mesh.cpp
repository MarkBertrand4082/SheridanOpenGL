#include "Mesh.h"
#include "Shader.h"

Mesh::Mesh()
{
	m_shader = nullptr;
	m_vertexBuffer = 0;
}

Mesh::~Mesh()
{
}

void Mesh::Create(Shader* _shader)
{
	m_shader = _shader;

	m_vertexData = { -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f };
	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW);
}

void Mesh::Cleanup()
{
	glDeleteBuffers(1, &m_vertexBuffer);
}

void Mesh::Render()
{
	glUseProgram(m_shader->GetProgramID());

	glEnableVertexAttribArray(m_shader->GetAttrVertices());
	glVertexAttribPointer(m_shader->GetAttrVertices(),
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(m_shader->GetAttrVertices());
}