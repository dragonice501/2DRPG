#include "SceneTownShop.h"

SceneTownShop::~SceneTownShop()
{
    
}

void SceneTownShop::Setup(static SDL_Renderer* renderer)
{
    SceneExploration::Setup(renderer);

    LoadShopItems();

    if (GameManager::GetSceneEntranceIndex() == -1)
    {
        mSpawnPositions.clear();
        mSpawnPositions.push_back(Vec2(4.0f, 6.0f) * TILE_SIZE);
        mSpawnPositions.push_back(Vec2(4.0f, 6.0f) * TILE_SIZE);
        mSpawnPositions.push_back(Vec2(4.0f, 6.0f) * TILE_SIZE);
        mSpawnPositions.push_back(Vec2(4.0f, 6.0f) * TILE_SIZE);

        for (int i = 0; i < 4; i++)
        {
            mSpawnDirections.push_back(Vec2(0.0f, 1.0f));
        }
    }

    SceneExploration::SetupCharacters();
}

void SceneTownShop::Shutdown()
{
    SceneExploration::Shutdown();
}

void SceneTownShop::Input()
{
    SceneExploration::Input();

    if (mExplorationState == ES_SHOPPING)
    {
        if (InputManager::UpPressed() && mShopMenu.GetCurrentButton()->OnUpAction)
        {
            mShopMenu.GetCurrentButton()->OnUpAction();
        }
        else if (InputManager::DownPressed() && mShopMenu.GetCurrentButton()->OnDownAction)
        {
            mShopMenu.GetCurrentButton()->OnDownAction();
        }
        else if (InputManager::RightPressed() && mShopMenu.GetCurrentButton()->OnRightAction)
        {
            mShopMenu.GetCurrentButton()->OnRightAction();
        }
        else if (InputManager::LeftPressed() && mShopMenu.GetCurrentButton()->OnLeftAction)
        {
            mShopMenu.GetCurrentButton()->OnLeftAction();
        }
        else if (InputManager::AcceptPressed() && mShopMenu.GetCurrentButton()->OnAcceptAction)
        {
            mShopMenu.GetCurrentButton()->OnAcceptAction();
        }
        else if (InputManager::CancelPressed() && mShopMenu.GetCurrentButton()->OnCancelAction)
        {
            mShopMenu.GetCurrentButton()->OnCancelAction();
        }
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

        GraphicsManager::DrawSpriteRect(mBattleIconsTexture, cursorSpriteRect, destRect);
    }
    else
    {
        SceneExploration::DrawCursor();
    }
}

void SceneTownShop::SetupShopMenu()
{
    mShopMenu.mMainBuyButton.OnAcceptAction = [this]()
    {

    };

    mShopMenu.mMainSellButton.OnAcceptAction = [this]()
    {

    };

    mShopMenu.mMainExitButton.OnAcceptAction = [this]()
    {
        mExplorationState = ES_EXPLORING;
    };
}

void SceneTownShop::LoadShopItems()
{
    std::string fileName;

    fileName = "./assets/" + mFileName + "Items.txt";
    std::ifstream file(fileName);
    std::string type;
    while (file >> type)
    {
        if (type == "Weapons")
        {
            while (file >> type)
            {
                if (type == "End") break;
                
                Weapon newWeapon(type);
                mWeapons.push_back(newWeapon);
            }
        }
    }
}