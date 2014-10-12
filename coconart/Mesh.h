#pragma once
#include "Prerequites.h"

namespace Coconart
{

	class Vertex
	{
	public:
		vec2 pos;
		vec3 uv;
	};

	class Mesh
	{
	private:
		uint vao;
		uint vbo_v;
		uint vbo_i;

	public:
		vector <Vertex> vertices;
		vector <uint> indices;

		Mesh();
		~Mesh();

		void CreateGeometry();
		void DestroyGeometry();
		void UpdateGeometry();

		void Draw();
	};

}