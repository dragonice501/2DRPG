#pragma once

#include <SDL.h>

const int FPS = 60;
const int MILLISECONDS_PER_FRAME = 1000 / FPS;

class Engine
{
public:
	static Engine& Instance()
	{
		static Engine* instance = new Engine();
		return *instance;
	}
	static SDL_Rect& Camera() { return camera; }
	static void SetIsRunning(const bool running);

	bool Init();
	void Run();
	void Destroy();

	static int mWindowWidth;
	static int mWindowHeight;
	static int mapWidth;
	static int mapHeight;

private:
	Engine();
	~Engine() {}
	
	static SDL_Rect camera;
	static bool isRunning;

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	int millisecondsPreviousFrame;
	bool isDebug;
};

