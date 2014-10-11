#pragma once
#include "Prerequites.h"
#include "Context.h"

namespace Coconart
{

	class Root
	{
	private:
		Root() {};
		Root(Root const&) {};
		Root& operator=(Root const&) {};

	public:
		static Root& GetSingleton()
		{
			static Root singleton;
			return singleton;
		}

		ContextSDL context;
	};

	static Root& ROOT = Root::GetSingleton();

}



/*
#pragma once
#include "Prerequites.h"

class Root
{
private:
Root() {};
Root(Root const&) {};
Root& operator=(Root const&) {};

bool running = true;

SDL_Window* window = NULL;
SDL_GLContext glContext = NULL;

static const int WindowWidth = 800;
static const int WindowHeight = 600;

void OnEvent(SDL_Event* Event);
bool Init();
void Loop();
void Render();
void Cleanup();

public:
static Root& GetSingleton()
{
static Root singleton;
return singleton;
}

int StartApplication();
};

static Root& ROOT = Root::GetSingleton();*/