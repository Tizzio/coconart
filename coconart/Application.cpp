#include "Application.h"
#include "Coconart.h"
using namespace NJine;


Shader basic_shader;
Mesh basic_mesh;
Texture basic_texture;

void Application::Init()
{
	if (basic_shader.Load("data\\shaders\\basic.glsl", "Basic"))
	{
		cout << "shader loaded" << endl;
	}

	basic_mesh.CreateGeometry();
	basic_mesh.vertices.resize(3);
	basic_mesh.indices.resize(3);
	basic_mesh.vertices[0].pos = vec2(0.0, 0.0);
	basic_mesh.vertices[1].pos = vec2(0.6, 0.1);
	basic_mesh.vertices[2].pos = vec2(0.5, 0.8);
	basic_mesh.vertices[0].uv = vec2(0.0, 1.0);
	basic_mesh.vertices[1].uv = vec2(1.0, 1.0);
	basic_mesh.vertices[2].uv = vec2(0.0, 0.0);
	basic_mesh.indices[0] = 0;
	basic_mesh.indices[1] = 1;
	basic_mesh.indices[2] = 2;

	basic_mesh.UpdateGeometry();


	basic_texture.Create();
	basic_texture.Load("data\\textures\\SS3.png");
	basic_texture.Update();
}

void Application::Loop()
{
	glDisable(GL_MULTISAMPLE);
	glDisable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.5f, 0.5f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT/* | GL_DEPTH_BUFFER_BIT*/);

	basic_shader.Bind();
	basic_texture.Bind(0);
	basic_mesh.Draw();
}

void Application::End()
{

}