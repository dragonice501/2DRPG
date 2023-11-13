#include "SceneMainMenu.h"

void SceneMainMenu::Setup(SDL_Renderer* renderer)
{
    GameManager::CheckGameSaveExists();
    mMainMenu.LoadMainMenu();

    std::string type;
    std::ifstream battleIconsFile("./assets/files/BattleIcons.txt");
    while (battleIconsFile >> type)
    {
        if (type == "Cursor")
        {
            Sprite newSprite;

            battleIconsFile >> newSprite.srcRect.x >> newSprite.srcRect.y >> newSprite.srcRect.w >> newSprite.srcRect.h;
            mBattleIconsMap.emplace("Cursor", newSprite);
        }
    }

    mBackgroundSprite.mAssetID = "MainMenuBackground";

    AudioManager::GetMusic("MainMenu.mp3");
    AudioManager::FadeInMusic("MainMenu.mp3", 1000);

    AssetManager::CreateMenuIconsTexture();
    AssetManager::CreateCharacterTexture("Paladin");
    AssetManager::CreateCharacterTexture("Dancer");
    AssetManager::CreateCharacterTexture("Mage");
    AssetManager::CreateCharacterTexture("Knight");
    AssetManager::CreateAsset("MainMenuBackground", "./assets/images/MainMenu.png");
}

void SceneMainMenu::Shutdown()
{
    AudioManager::FadeOutMusic(500);
    AssetManager::DestroyMenuIconsTexture();
    AssetManager::DestroyAssetMap();
}

void SceneMainMenu::Input()
{
    if (InputManager::UpPressed() && mMainMenu.GetCurrentButton()->OnUpAction)
    {
        mMainMenu.GetCurrentButton()->OnUpAction();
        AudioManager::PlaySFX("blip.wav");
    }
    else if (InputManager::DownPressed() && mMainMenu.GetCurrentButton()->OnDownAction)
    {
        mMainMenu.GetCurrentButton()->OnDownAction();
        AudioManager::PlaySFX("blip.wav");
    }
    else if (InputManager::RightPressed() && mMainMenu.GetCurrentButton()->OnRightAction)
    {
        mMainMenu.GetCurrentButton()->OnRightAction();
        AudioManager::PlaySFX("blip.wav");
    }
    else if (InputManager::LeftPressed() && mMainMenu.GetCurrentButton()->OnLeftAction)
    {
        mMainMenu.GetCurrentButton()->OnLeftAction();
        AudioManager::PlaySFX("blip.wav");
    }
    else if (InputManager::AcceptPressed() && mMainMenu.GetCurrentButton()->OnAcceptAction)
    {
        mMainMenu.GetCurrentButton()->OnAcceptAction();
    }
    else if (InputManager::CancelPressed() && mMainMenu.GetCurrentButton()->OnCancelAction)
    {
        mMainMenu.GetCurrentButton()->OnCancelAction();
    }
}

void SceneMainMenu::Update(const float dt)
{
}

void SceneMainMenu::Render(SDL_Rect& camera)
{
    GraphicsManager::DrawSpriteRect(AssetManager::GetAsset(mBackgroundSprite.mAssetID));
	mMainMenu.Render();

    DrawCursor();
}

void SceneMainMenu::ExitMenu()
{
}

void SceneMainMenu::DrawCursor()
{
    SDL_Rect& cursorSpriteRect = mBattleIconsMap.at("Cursor").srcRect;

    SDL_Rect destRect;

    destRect =
    {
        static_cast<int>(mMainMenu.GetCurrentButton()->mPosition.x - cursorSpriteRect.w * BATTLE_CURSOR_SCALE - 5),
        static_cast<int>(mMainMenu.GetCurrentButton()->mPosition.y),
        cursorSpriteRect.w * BATTLE_CURSOR_SCALE,
        cursorSpriteRect.h * BATTLE_CURSOR_SCALE
    };

    GraphicsManager::DrawSpriteRect(AssetManager::GetMenuIconsTexture(), cursorSpriteRect, destRect);
}