#pragma once

#include "Scene.h"

#include "../UI/MenuMainMenu.h"


class SceneMainMenu : public Scene
{
public:
	virtual void Setup(static SDL_Renderer* renderer);
	virtual void Shutdown() override;

	virtual void Input() override;
	virtual void Update(const float dt) override;
	virtual void Render(static SDL_Rect& camera) override;

	virtual void ExitMenu() override;

private:
	MenuMainMenu mMainMenu;
};