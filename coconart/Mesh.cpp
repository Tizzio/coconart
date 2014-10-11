#include "Mesh.h"
using namespace NJine;

Mesh::Mesh()
{
	vao = 0;
	vbo_v = 0;
	vbo_i = 0;
}
Mesh::~Mesh()
{
	//Release();
}

void Mesh::CreateGeometry()
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo_v);
	glGenBuffers(1, &vbo_i);

	glBindVertexArray(vao);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_i);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_v);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	//glEnableVertexAttribArray(2);

	uint offset = 0;
	//posizione
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offset);
	offset += sizeof(((Vertex*)0)->pos);
	//Texcoord
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offset);
	//offset += sizeof(((Vertex*)0)->uv);

	glBindVertexArray(0);
}
void Mesh::DestroyGeometry()
{
	glDeleteBuffers(1, &vbo_v);
	glDeleteBuffers(1, &vbo_i);
	glDeleteVertexArrays(1, &vao);
}
void Mesh::UpdateGeometry()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_i);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint)* indices.size(), &indices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_v);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* vertices.size(), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void Mesh::Draw()
{
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}