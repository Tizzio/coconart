#pragma once
#include "Prerequites.h"

namespace NJine
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

}