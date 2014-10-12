#define _CRT_SECURE_NO_WARNINGS
#include "Texture.h"
#include "Libraries\lodepng\lodepng.h"
#include "Libraries\jsoncpp\json.h"

#include <fstream>
using namespace std;

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
		cout << "error loading image" << endl;
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

TextureArray::TextureArray()
{
	tex_id = 0;
	width = 0;
	height = 0;
	layer_num = 0;
}

void TextureArray::Create()
{
	glGenTextures(1, &tex_id);
}

void TextureArray::Delete()
{
	glDeleteTextures(1, &tex_id);
}

bool TextureArray::Load(const string& filename)
{
	std::ifstream t;
	int length;
	t.open(filename);					// open input file
	if (!t)	{ return false; }			//failed to open file
	t.seekg(0, std::ios::end);			// go to the end
	length = t.tellg();					// report location (this is the length)
	if (length == 0) { return false; }	//no data
	t.seekg(0, std::ios::beg);			// go back to the beginning
	char* buffer = new char[length];	// allocate memory for a buffer of appropriate dimension
	t.read(buffer, length);				// read the whole file into the buffer
	t.close();

	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(buffer, buffer + length, root, false);
	delete buffer;
	if (!parsingSuccessful)
	{
			cout << "Failed to parse JSON" << endl
			<< reader.getFormattedErrorMessages()
			<< endl;
			return false;
	}
	const Json::Value tex_width = root["width"];
	const Json::Value tex_height = root["height"];
	const Json::Value tex_array = root["layers"];
	if (!(tex_width.isUInt() && tex_height.isUInt() && tex_array.isArray()))
	{
		return false;
	}
	width = tex_width.asUInt();
	height = tex_height.asUInt();
	layer_num = tex_array.size();
	data.resize(width * height * layer_num);
	for (uint index = 0; index < layer_num; index++)
	{
		const Json::Value tex_name = tex_array[index];
		if (tex_name.isString())
		{
			LoadSingleTexture(tex_name.asString(), index);
		}
	}
	return true;
}

void TextureArray::Update()
{
	glBindTexture(GL_TEXTURE_2D_ARRAY, tex_id);
	glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, width, height, layer_num, 0, GL_RGBA, GL_UNSIGNED_BYTE, &data[0]);
	glTexParameterf(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}

void TextureArray::Bind(const uint& stage)
{
	glActiveTexture(GL_TEXTURE0 + stage);
	glBindTexture(GL_TEXTURE_2D_ARRAY, tex_id);
}

bool TextureArray::LoadSingleTexture(const string& filename, uint layer)
{
	std::vector<unsigned char> png;
	std::vector<unsigned char> image; //the raw pixels
	lodepng::load_file(png, filename);

	uint new_width, new_height;
	unsigned error = lodepng::decode(image, new_width, new_height, png);

	if (error || (width != new_width) || (height != new_height))
	{
		cout << "error loading image" << endl;
		printf(lodepng_error_text(error));
		return false;
	}
	else
	{
		uint image_size = width * height;
		uint base_index = image_size * layer;
		memcpy(&data[base_index], &image[0], image_size * 4);
		return true;
	}
}


/*bool TextureArray::Load(const string& filename)
{
width = 512;
height = 512;
layer_num = 3;
data.resize(width * height * layer_num);
LoadSingleTexture("data\\textures\\SS3.png", 0);
LoadSingleTexture("data\\textures\\compe.png", 1);
LoadSingleTexture("data\\textures\\buddha.png", 2);
return true;
}*/