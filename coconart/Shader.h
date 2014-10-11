#pragma once
#include "Prerequites.h"
#include <string>
using namespace std;

namespace Coconart
{

	class Shader
	{
	private:
		int effect;
		GLint program;
	public:
		map <string, GLint> locations;

		Shader();
		~Shader();
		bool Load(const string& filename, const string& program_name);
		void Release();
		void Bind();
		void CheckLocations();
	};

}