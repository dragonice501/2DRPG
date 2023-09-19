#pragma once

#include "../Scenes/Scene.h"
#include "../Scenes/SceneBattle.h"
#include "../Scenes/SceneOverworld.h"
#include "../Scenes/SceneTown.h"

#include "../Objects/EnemyEncounter.h"

#include "../Managers/GraphicsManager.h"

#include "../Utils/Utils.h"

#include <memory>

class SceneManager
{
public:
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