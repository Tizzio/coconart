#pragma once
#include "Prerequites.h"

namespace Coconart
{

	class Texture
	{
		GLuint tex_id;
	public:
		vector<u8vec4> data;
		uint width;
		uint height;

		Texture();

		void Create();
		void Delete();
		bool Load(const string& filename);
		void Update();
		void Bind(const uint& stage);
	};

	class TextureArray
	{
		GLuint tex_id;

	public:
		vector<u8vec4> data;
		uint width;
		uint height;
		uint layer_num;

		TextureArray();

		void Create();
		void Delete();
		bool Load(const string& filename);
		void Update();
		void Bind(const uint& stage);

	private:
		bool LoadSingleTexture(const string& filename, uint layer);
	};

}