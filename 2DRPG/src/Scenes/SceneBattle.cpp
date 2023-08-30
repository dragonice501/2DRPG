#include "SceneBattle.h"

SceneBattle::SceneBattle(ETerrainType terrain)
{
	switch (terrain)
	{
		case BRIDGE:
		{
			mBackgroundImageFilePath = "./assets/BattlePlain.png";
			break;
		}
		case FOREST:
		{
			mBackgroundImageFilePath = "./assets/BattleForest.png";
			break;
		}
		case PLAIN:
		{
			mBackgroundImageFilePath = "./assets/BattlePlain.png";
			break;
		}
		case ROAD:
		{
			mBackgroundImageFilePath = "./assets/BattlePlain.png";
			break;
		}
		case THICKET:
		{
			mBackgroundImageFilePath = "./assets/BattleThicket.png";
			break;
		}
	}
}

void SceneBattle::Setup(SDL_Renderer* renderer)
{
	SDL_Surface* surface = IMG_Load(mBackgroundImageFilePath.c_str());
	if (surface)
	{
		mBackgroundTexture = SDL_CreateTextureFromSurface(renderer, surface);
	}
}

void SceneBattle::Shutdown()
{
}

void SceneBattle::Input()
{
	if (InputManager::UpPressed())
	{
		mBattleMenuIndex--;
		if (mBattleMenuIndex < 0) mBattleMenuIndex = mBattleMenuIndexOptions - 1;
	}
	if (InputManager::DownPressed())
	{
		mBattleMenuIndex++;
		if (mBattleMenuIndex >= mBattleMenuIndexOptions) mBattleMenuIndex = 0;
	}

	if (InputManager::EPressed())
	{
		if (mBattleMenuIndex == 0)
		{
			
		}
		else if (mBattleMenuIndex == 1)
		{

		}
		else if (mBattleMenuIndex == 2)
		{
			
		}
		else if (mBattleMenuIndex == 3)
		{
			SceneManager::SetSceneToLoad(OVERWORLD, -1, UNDEFINED, true);
		}
	}
}

void SceneBattle::Update(const float dt)
{
}

void SceneBattle::Render(SDL_Renderer* renderer, SDL_Rect& camera)
{
	GraphicsManager::DrawBattleBackground(mBackgroundTexture);

	SDL_Rect rect = GraphicsManager::DrawUIBox(
		GraphicsManager::WindowWidth() / 2, 
		GraphicsManager::WindowHeight() - BATTLE_MENU_HEIGHT - DIALOGUE_BOX_BORDER_SIZE * 2,
		BATTLE_MENU_WIDTH,
		BATTLE_MENU_HEIGHT);
	GraphicsManager::DrawUISelector(rect.x, rect.y + 30 * mBattleMenuIndex, rect.w, 30);

	GraphicsManager::DrawString(rect.x + TEXT_PADDING, rect.y + TEXT_PADDING, "Fight", 0xFFFFFFFF);
	GraphicsManager::DrawString(rect.x + TEXT_PADDING, rect.y + TEXT_PADDING + 30, "Magic", 0xFFFFFFFF);
	GraphicsManager::DrawString(rect.x + TEXT_PADDING, rect.y + TEXT_PADDING + 60, "Item", 0xFFFFFFFF);
	GraphicsManager::DrawString(rect.x + TEXT_PADDING, rect.y + TEXT_PADDING + 90, "Run", 0xFFFFFFFF);
}