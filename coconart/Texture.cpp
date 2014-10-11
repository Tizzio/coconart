#define _CRT_SECURE_NO_WARNINGS
#include "Texture.h"
#include "lodepng.h"
using namespace Coconart;

Texture::Texture()
{
	tex_id = 0;
	width = 0;
	height = 0;
}

void Texture::Create()
{
	glGenTextures(1, &tex_id);
}

void Texture::Delete()
{
	glDeleteTextures(1, &tex_id);
}

bool Texture::Load(const string& filename)
{
	std::vector<unsigned char> png;
	std::vector<unsigned char> image; //the raw pixels
	lodepng::load_file(png, filename);
	unsigned error = lodepng::decode(image, width, height, png);
	
	if (error)
	{
		cout << "error loading image" << endl;;
		printf(lodepng_error_text(error));
		return false;
	}
	else
	{
		cout << "success loading image" << endl;
		data.resize(width * height);
		memcpy(&data[0], &image[0], width * height * 4);
		return true;
	}
}

void Texture::Update()
{
	glBindTexture(GL_TEXTURE_2D, tex_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &data[0]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Bind(const uint& stage)
{
	glActiveTexture(GL_TEXTURE0 + stage);
	glBindTexture(GL_TEXTURE_2D, tex_id);
}