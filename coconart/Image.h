#pragma once
#include "Prerequites.h"
#include "Texture.h"

namespace Coconart
{

	class ImageVertex
	{
	public:
		vec2 pos;
		vec3 uv;
		u8vec4 col;
	};

	class Image
	{
	private:
		uint vao;
		uint vbo_v;
		uint vbo_i;

	public:
		TextureArray* texture;
		ImageVertex v1, v2;

		Image();
		~Image();

		void CreateGeometry();
		void DestroyGeometry();
		void UpdateGeometry();

		void Draw();
	};

	bool LoadImages(vector<Image*>& images, const string& filename);

}