#pragma once

#include "../ECS/ECS.h"
#include "../AssetStore/AssetStore.h"
#include "../EventBus/EventBus.h"

#include <SDL.h>

const int FPS = 60;
const int MILLISECONDS_PER_FRAME = 1000 / FPS;

class Engine
{
public:
	static Engine& Instance();
	static const SDL_Rect& Camera();
	static void SetIsRunning(const bool running);

	bool Init();
	void Run();
	void Destroy();

	static int mWindowWidth;
	static int mWindowHeight;
	static int mapWidth;
	static int mapHeight;
	static SDL_Rect camera;
	static bool isRunning;

private:
	Engine();
	~Engine() {}

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;

	std::unique_ptr<Registry> mRegistry;
	std::unique_ptr<AssetStore> mAssetStore;
	std::unique_ptr<EventBus> mEventBus;

	int millisecondsPreviousFrame;
	bool isDebug;
};

