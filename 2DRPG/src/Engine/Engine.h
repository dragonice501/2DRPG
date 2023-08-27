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
	static void SetIsRunning(const bool running);

	bool Init();
	void Run();
	void Destroy();

private:
	Engine();
	~Engine() {}
	
	static bool isRunning;
	int millisecondsPreviousFrame;
	bool isDebug;
};

