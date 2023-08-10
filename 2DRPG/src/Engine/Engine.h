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
	Engine();
	~Engine();

	void Init();
	void Run();
	void Destroy();

	void Setup();
	void Input();
	void Update();
	void Draw();

	static int mWindowWidth;
	static int mWindowHeight;
	static int mapWidth;
	static int mapHeight;

private:
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	SDL_Rect camera;

	std::unique_ptr<Registry> mRegistry;
	std::unique_ptr<AssetStore> mAssetStore;
	std::unique_ptr<EventBus> mEventBus;

	int millisecondsPreviousFrame;
	bool isRunning;
	bool isDebug;
};

