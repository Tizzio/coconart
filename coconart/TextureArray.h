/*#pragma once
#include "Prerequites.h"
#include "ResourceTemplate.h"

namespace Coconart
{

	class Texture : public Resource
	{
	private:
		friend class BaseResourceManager<Texture>;
		Texture(const string& name) : Resource(name) {}
		Texture(const Texture& res);

		TextureArray* tex_array;

		vector<u8vec4> data;
		uint width;
		uint height;

	public:
		bool Load(const string& filename);
		void Resize(const uint& w, const uint& h);
		uint GetWidth();
		uint GetHeight();
		u8vec4* GetData();

		bool Attach(TextureArray* texture_array);
		void Detach();
		bool IsAttached();
		TextureArray* GetTexArray();
	};


	class TextureArray
	{
		GLuint tex_id;
		uint width;
		uint height;
		uint layer_num;
		vector<Texture*> textures;

	public:
		TextureArray();

		void Create();
		void Delete();
		void Update();
		void Bind(const uint& stage);

	private:
		bool LoadSingleTexture(const string& filename, uint layer);
	};

}*/