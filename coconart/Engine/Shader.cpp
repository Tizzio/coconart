#include "Shader.h"
using namespace Coconart;

Shader::Shader()
{
	effect = 0;
	program = 0;
}

Shader::~Shader()
{
	Release();
}

void Shader::Bind()
{
	glUseProgram(program);
}

void Shader::Release()
{
	if (effect)
	{
		glfxDeleteEffect(effect);
	}
}

bool Shader::Load(const string& filename, const string& program_name)
{
	Release();

	effect = glfxGenEffect();

	if (!glfxParseEffectFromFile(effect, filename.c_str()))
	{
		std::string log = glfxGetEffectLog(effect);
		std::cout << "Error parsing effect: " << log << std::endl;
		return false;
	}

	program = glfxCompileProgram(effect, program_name.c_str());

	if (program < 0)
	{
		std::string log = glfxGetEffectLog(effect);
		std::cout << "Error compiling effect: " << log << std::endl;
		return false;
	}

	return true;
}

void Shader::CheckLocations()
{
	map <string, GLint>::iterator it;
	for (it = locations.begin(); it != locations.end(); it++)
	{
		it->second = glGetUniformLocation(program, it->first.c_str());
		if (it->second == 0xFFFFFFFF)
		{
			cout << " shader parameter \"" + it->first + "\" doesn't exist" << endl;
		}
	}
}