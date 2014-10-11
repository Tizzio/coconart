#pragma once
#include "Prerequites.h"

namespace Coconart
{
	class ContextSDL
	{
	private:

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
		int StartApplication(const uint& width, const uint& height);
		void CloseApplication();
	};
}