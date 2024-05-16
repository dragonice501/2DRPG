#pragma once

#include "Scene.h"
#include "SceneBattle.h"
#include "SceneMainMenu.h"
#include "SceneOverworld.h"
#include "SceneTown.h"
#include "SceneTownShop.h"

#include "EnemyEncounter.h"

#include "GraphicsManager.h"

#include "Utils.h"

#include <memory>

class SceneManager
{
public:
	static std::unique_ptr<Scene>& GetCurrentScene() { return mCurrentScene; }

	static void LoadScene();

	static void CurrentSceneInput();
	static void CurrentSceneUpdate(const float dt);
	static void CurrentSceneRender();

	static void CurrentSceneShutdown();

private:
	SceneManager() {};
	~SceneManager() {};

	static std::unique_ptr<Scene> mCurrentScene;
};