#include "SceneTownShop.h"

SceneTownShop::~SceneTownShop()
{
    
}

void SceneTownShop::Setup(static SDL_Renderer* renderer)
{
    SceneExploration::Setup(renderer);

    LoadShopItems();

    if (GameManager::LoadedGame())
    {
        for (int i = 0; i < 4; i++)
        {
            mSpawnPositions.push_back(GameManager::GetPreviousCharacterPosition(i));
            mSpawnDirections.push_back(GameManager::GetPreviousCharacterDirection(i));
        }
    }
    else if (GameManager::GetSceneEntranceIndex() == -1)
    {
        mSpawnPositions.clear();
        mSpawnPositions.push_back(Vec2(16.0f, 17.0f) * TILE_SIZE);
        mSpawnPositions.push_back(Vec2(17.0f, 17.0f) * TILE_SIZE);
        mSpawnPositions.push_back(Vec2(17.0f, 18.0f) * TILE_SIZE);
        mSpawnPositions.push_back(Vec2(16.0f, 18.0f) * TILE_SIZE);

        for (int i = 0; i < 4; i++)
        {
            mSpawnDirections.push_back(Vec2(0.0f, 1.0f));
        }
    }

    SceneExploration::SetupCharacters();

    AudioManager::GetMusic("Take some rest and eat some food!.wav");
    AudioManager::FadeInMusic("Take some rest and eat some food!.wav", 1000);
}

void SceneTownShop::Shutdown()
{
    SceneExploration::Shutdown();
}

void SceneTownShop::Input()
{
    if (mExplorationState == ES_SHOPPING)
    {
        if (InputManager::UpPressed() && mShopMenu.GetCurrentButton()->OnUpAction)
        {
            mShopMenu.GetCurrentButton()->OnUpAction();
            AudioManager::PlaySFX("blip.wav");
        }
        else if (InputManager::DownPressed() && mShopMenu.GetCurrentButton()->OnDownAction)
        {
            mShopMenu.GetCurrentButton()->OnDownAction();
            AudioManager::PlaySFX("blip.wav");
        }
        else if (InputManager::RightPressed() && mShopMenu.GetCurrentButton()->OnRightAction)
        {
            mShopMenu.GetCurrentButton()->OnRightAction();
            AudioManager::PlaySFX("blip.wav");
        }
        else if (InputManager::LeftPressed() && mShopMenu.GetCurrentButton()->OnLeftAction)
        {
            mShopMenu.GetCurrentButton()->OnLeftAction();
            AudioManager::PlaySFX("blip.wav");
        }
        else if (InputManager::AcceptPressed() && mShopMenu.GetCurrentButton()->OnAcceptAction)
        {
            mShopMenu.GetCurrentButton()->OnAcceptAction();
            AudioManager::PlaySFX("blip.wav");
        }
        else if (InputManager::CancelPressed() && mShopMenu.GetCurrentButton()->OnCancelAction)
        {
            mShopMenu.GetCurrentButton()->OnCancelAction();
            AudioManager::PlaySFX("blip.wav");
        }
    }
    else
    {
        SceneExploration::Input();
    }
}

void SceneTownShop::Update(const float dt)
{
    SceneExploration::Update(dt);
}

void SceneTownShop::Render(static SDL_Rect& camera)
{
    SceneExploration::Render(camera);

    if (mExplorationState == ES_SHOPPING)
    {
        mShopMenu.Render();
        DrawCursor();
    }
}

void SceneTownShop::DrawCursor()
{
    SDL_Rect& cursorSpriteRect = mBattleIconsMap.at("Cursor").srcRect;

    SDL_Rect destRect;

    if (mExplorationState == ES_SHOPPING)
    {
        destRect =
        {
            static_cast<int>(mShopMenu.GetCurrentButton()->mPosition.x - cursorSpriteRect.w * BATTLE_CURSOR_SCALE - 5),
            static_cast<int>(mShopMenu.GetCurrentButton()->mPosition.y),
            cursorSpriteRect.w * BATTLE_CURSOR_SCALE,
            cursorSpriteRect.h * BATTLE_CURSOR_SCALE
        };

        GraphicsManager::DrawSpriteRect(AssetManager::GetMenuIconsTexture(), cursorSpriteRect, destRect);
    }
    else
    {
        SceneExploration::DrawCursor();
    }
}

void SceneTownShop::SetupShopMenu()
{
    mShopMenu.mMainBuyButton.OnCancelAction = [this]()
    {
        mShopMenu.SetCurrentButton(&mShopMenu.mMainBuyButton);
        mExplorationState = ES_EXPLORING;
    };

    mShopMenu.mMainSellButton.OnCancelAction = [this]()
    {
        mShopMenu.SetCurrentButton(&mShopMenu.mMainBuyButton);
        mExplorationState = ES_EXPLORING;
    };

    mShopMenu.mMainExitButton.OnAcceptAction = [this]()
    {
        mShopMenu.SetCurrentButton(&mShopMenu.mMainBuyButton);
        mExplorationState = ES_EXPLORING;
    };
    mShopMenu.mMainExitButton.OnCancelAction = [this]()
    {
        mShopMenu.SetCurrentButton(&mShopMenu.mMainBuyButton);
        mExplorationState = ES_EXPLORING;
    };
}

void SceneTownShop::LoadShopItems()
{
    std::string fileName;

    fileName = "./assets/files/" + mFileName + "Items.txt";
    std::ifstream file(fileName);
    std::string type;
    while (file >> type)
    {
        if (type == "Weapons")
        {
            while (file >> type)
            {
                if (type == "End") break;
                
                mShopMenu.mWeapons.push_back(Weapon(type));
            }
        }
        else if (type == "Armour")
        {
            while (file >> type)
            {
                if (type == "End") break;

                mShopMenu.mArmour.push_back(Armour(type));
            }
        }
    }
}