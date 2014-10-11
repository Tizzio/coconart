#include "Context.h"
#include "Application.h"
using namespace Coconart;

bool ContextSDL::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		//Log("Unable to Init SDL: %s", SDL_GetError());
		return false;
	}

	/*if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
	//Log("Unable to Init hinting: %s", SDL_GetError());
	}*/

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 0);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 0);
	SDL_GL_SetAttribute(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE, 1);
	//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

	window = SDL_CreateWindow(
		"Coconart",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WindowWidth, WindowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	if (window == NULL)
	{
		//Log("Unable to create SDL Window: %s", SDL_GetError());
		return false;
	}

	glContext = SDL_GL_CreateContext(window);
	SDL_GL_SetSwapInterval(0);

	if (glContext == NULL)
	{
		cout << "There was an error creating the OpenGL context!\n";
		return false;
	}

	SDL_GL_MakeCurrent(window, glContext);

	glewExperimental = GL_TRUE;
	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		cout << string("Error in glew: ") + ((char*)glewGetErrorString(res)) << endl;
		return false;
	}
	if (!glewIsSupported("GL_VERSION_3_3"))
	{
		cout << "OpenGL 3.3 required!" << endl;
		return false;
	}
	glGetError();
	glGetString(GL_VERSION);
	cout << string("Opengl Version: ") + ((char*)glGetString(GL_VERSION)) << endl;
	Application::Init();
	return true;
}

void ContextSDL::OnEvent(SDL_Event* Event)
{
	if (Event->type == SDL_QUIT)  {
		running = false;
	}
}

void ContextSDL::Loop()
{
	Application::Loop();
}

void ContextSDL::Render()
{
	/*glDisable(GL_MULTISAMPLE);
	glDisable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(0.5f, 0.5f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);*/

	SDL_GL_SwapWindow(window);
}

void ContextSDL::Cleanup()
{
	Application::End();

	int error = glGetError();
	switch (error)
	{
	case GL_NO_ERROR:						cout << "GL ERROR: GL_NO_ERROR" << endl; break;
	case GL_INVALID_ENUM:					cout << "GL ERROR: GL_INVALID_ENUM" << endl; break;
	case GL_INVALID_VALUE:					cout << "GL ERROR: GL_INVALID_VALUE" << endl; break;
	case GL_INVALID_OPERATION:				cout << "GL ERROR: GL_INVALID_OPERATION" << endl; break;
	case GL_STACK_OVERFLOW:					cout << "GL ERROR: GL_STACK_OVERFLOW" << endl; break;
	case GL_STACK_UNDERFLOW:				cout << "GL ERROR: GL_STACK_UNDERFLOW" << endl; break;
	case GL_OUT_OF_MEMORY:					cout << "GL ERROR: GL_OUT_OF_MEMORY" << endl; break;
	case GL_INVALID_FRAMEBUFFER_OPERATION:	cout << "GL ERROR: GL_INVALID_FRAMEBUFFER_OPERATION" << endl; break;
	case GL_TABLE_TOO_LARGE:				cout << "GL ERROR: GL_TABLE_TOO_LARGE" << endl; break;
	}
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);

	SDL_Quit();
}

int ContextSDL::StartApplication(const uint& width, const uint& height)
{
	if (!Init()) return 0;

	SDL_Event event;

	while (running)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			OnEvent(&event);
			if (event.type == SDL_QUIT) running = false;
		}

		Loop();
		Render();

		SDL_Delay(1);
	}

	Cleanup();

	getchar();
	return 1;
}

void ContextSDL::CloseApplication()
{
	running = false;
}