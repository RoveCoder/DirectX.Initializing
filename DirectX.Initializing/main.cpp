#include <SDL.h>
#include "Renderer.h"

int main(int argc, char** argv)
{
	// Setup SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", SDL_GetError(), nullptr);
		return -1;
	}

	// Create the window
	int window_width = 800;
	int window_height = 600;

	SDL_Window* window = SDL_CreateWindow("DirectX", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE);
	if (window == nullptr)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", SDL_GetError(), nullptr);
		return -1;
	}

	// Create renderer
	Renderer* renderer = new Renderer(window);
	if (!renderer->Init())
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Renderer::Init failed", nullptr);
		return -1;
	}

	// Main loop
	bool running = true;
	while (running)
	{
		SDL_Event e;
		if (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
				running = false;
				break;

			case SDL_WINDOWEVENT:
				switch (e.window.event)
				{
				case SDL_WINDOWEVENT_RESIZED:
					renderer->Resize(e.window.data1, e.window.data2);
					break;
				}
			}
		}
		else
		{
			renderer->Render();
		}
	}

	// Cleanup
	renderer->Quit();
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}