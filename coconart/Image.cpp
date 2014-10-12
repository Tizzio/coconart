#include "Image.h"
#include "Libraries\jsoncpp\json.h"
#include "Utility.h"
using namespace Coconart;

Image::Image()
{
	vao = 0;
	vbo_v = 0;
	vbo_i = 0;
	texture = NULL;
}
Image::~Image()
{
	//Release();
}

void Image::CreateGeometry()
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
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(ImageVertex), (void*)offset);
	offset += sizeof(((ImageVertex*)0)->pos);
	//Texcoord
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ImageVertex), (void*)offset);
	offset += sizeof(((ImageVertex*)0)->uv);
	//colore
	glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(ImageVertex), (void*)offset);
	//offset += sizeof(((ImageVertex*)0)->col);

	glBindVertexArray(0);
}
void Image::DestroyGeometry()
{
	glDeleteBuffers(1, &vbo_v);
	glDeleteBuffers(1, &vbo_i);
	glDeleteVertexArrays(1, &vao);
}
void Image::UpdateGeometry()
{
	ImageVertex vertices[4];
	uint indices[6];

	vertices[0] = v1;
	vertices[1] = v1;
	vertices[1].pos.y = v2.pos.y;
	vertices[1].uv.y = v2.uv.y;
	vertices[2] = v2;
	vertices[3] = v2;
	vertices[3].pos.x = v1.pos.x;
	vertices[3].uv.x = v1.uv.x;

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 0;
	indices[4] = 2;
	indices[5] = 3;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_i);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_v);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void Image::Draw()
{
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

bool Coconart::LoadImages(vector<Image*>& images, const string& filename)
{
	Json::Value root;
	if (!JsonLoad(root, filename)) { return false; }

	images.resize(root.size());
	for (uint index = 0; index < images.size(); index++)
	{
		images[index] = new Image();
		Image& image = *images[index];
		const Json::Value json_image = root[index];

		image.v1.uv.x = json_image[0].asFloat();
		image.v1.uv.y = json_image[1].asFloat();
		image.v2.uv.x = json_image[2].asFloat();
		image.v2.uv.y = json_image[3].asFloat();
		image.v1.uv.z = image.v2.uv.z = json_image["layer"].asFloat();

		image.v1.pos = vec2(image.v1.uv);
		image.v2.pos = vec2(image.v2.uv);
	}

	return true;
}