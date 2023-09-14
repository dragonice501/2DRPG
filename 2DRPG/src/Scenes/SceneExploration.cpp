#include "SceneExploration.h"

SceneExploration::SceneExploration()
{
    
}

SceneExploration::~SceneExploration()
{
}

void SceneExploration::Setup(SDL_Renderer* renderer)
{
    std::string fileName = "./assets/" + mFileName + "TileMap.png";
    SDL_Surface* surface = IMG_Load(fileName.c_str());
    if (surface)
    {
        mTileMap = SDL_CreateTextureFromSurface(renderer, surface);
    }
    SDL_FreeSurface(surface);

    int i = 0;
    Vec2 spawnPosition;

    fileName = "./assets/" + mFileName + "SaveFile.txt";
    std::ifstream file(fileName);
    std::string type;
    while (file >> type)
    {
        if (type == "MapSize")
        {
            file >> mMapWidth >> mMapHeight;
        }
        else if (type == "SceneEntrance")
        {
            int sceneName;
            int sceneEntranceIndex;
            int sceneEntrancePosX;
            int sceneEntrancePosY;
            int sceneEntranceOffsetX;
            int sceneEntranceOffsetY;
            file >> sceneName >> sceneEntranceIndex >> sceneEntrancePosX >> sceneEntrancePosY >> sceneEntranceOffsetX >> sceneEntranceOffsetY;

            SceneEntrance newEntrance =
            {
                Vec2(sceneEntrancePosX, sceneEntrancePosY) * TILE_SIZE,
                Vec2(sceneEntranceOffsetX, sceneEntranceOffsetY) * TILE_SIZE,
                sceneName,
                sceneEntranceIndex
            };

            mSceneEntrances.push_back(newEntrance);
        }
        else if (type == "Npc")
        {
            std::string npcName;
            int npcXPos;
            int npcYPos;
            std::string dialogueFile;

            file >> npcName >> npcXPos >> npcYPos >> dialogueFile;

            Vec2 position = { static_cast<float>(npcXPos * TILE_SIZE), static_cast<float>(npcYPos * TILE_SIZE) };

            Actor newActor;
            newActor.Init(npcName, position, renderer);
            newActor.LoadDialogue(dialogueFile);
            mActors.push_back(newActor);
        }
        else if (type == "Tile")
        {
            int tileType;
            file >> tileType;

            Tile newTile =
            {
                static_cast<size_t>(tileType),
                Vec2((i % mMapWidth) * TILE_SIZE, (i / mMapWidth) * TILE_SIZE)
            };

            mTiles.push_back(newTile);
            i++;
        }
    }

    EnemyEncounter newEncounter;
    fileName = "./assets/" + mFileName + "Encounters.txt";
    std::ifstream encountersFile(fileName);
    while (encountersFile >> type)
    {
        if (type == "End")
        {
            mEnemyEncounters.push_back(newEncounter);

            newEncounter.enemyNames.clear();
            newEncounter.enemyPositions.clear();
        }
        else
        {
            int enemyPosition;

            encountersFile >> enemyPosition;

            newEncounter.enemyNames.push_back(type);
            newEncounter.enemyPositions.push_back(enemyPosition);
        }
    }
}

void SceneExploration::Shutdown()
{
    SDL_DestroyTexture(mTileMap);
}

void SceneExploration::Input()
{
    if (InputManager::OPressed())
    {
        if (mExplorationState == ES_EXPLORING) mExplorationState = ES_MENUING;
        else mExplorationState = ES_EXPLORING;
    }

    if (InputManager::EPressed())
    {
        if (mExplorationState == ES_MENUING && mPartyMenuIndex == mPartyMenuIndexOptions - 1) mExplorationState = ES_EXPLORING;
    }

    if (InputManager::UpPressed())
    {
        switch (mExplorationState)
        {
            case ES_MENUING:
            {
                mPartyMenuIndex--;
                if (mPartyMenuIndex < 0) mPartyMenuIndex = mPartyMenuIndexOptions - 1;
                break;
            }
        }
    }

    if (InputManager::DownPressed())
    {
        switch (mExplorationState)
        {
            case ES_MENUING:
            {
                mPartyMenuIndex++;
                if (mPartyMenuIndex >= mPartyMenuIndexOptions) mPartyMenuIndex = 0;
                break;
            }
        }
    }
}

void SceneExploration::Update(const float dt)
{
    
}

void SceneExploration::Render(static SDL_Renderer* renderer, static SDL_Rect& camera)
{
    for (int i = 0; i < mTiles.size(); i++)
    {
        SDL_Rect srcRect =
        {
            mTiles[i].spriteIndex % SPRITE_SHEET_SIZE * TILE_SIZE,
            mTiles[i].spriteIndex / SPRITE_SHEET_SIZE * TILE_SIZE,
            TILE_SIZE,
            TILE_SIZE
        };

        SDL_Rect destRect =
        {
            mTiles[i].position.x * TILE_SPRITE_SCALE - GraphicsManager::Camera().x,
            mTiles[i].position.y * TILE_SPRITE_SCALE - GraphicsManager::Camera().y,
            TILE_SIZE * TILE_SPRITE_SCALE,
            TILE_SIZE * TILE_SPRITE_SCALE
        };

        GraphicsManager::DrawSpriteRect(mTileMap, srcRect, destRect);
    }
}

void SceneExploration::DrawPartyMenu(SDL_Renderer* renderer)
{
    SDL_Rect rect;
    std::string string;

    string = std::to_string(PlayerManager::GetPartyMoney()) + " g";

    int stringLength = 9 * Font::fontWidth * TEXT_SIZE + Font::fontSpacing * 9 * TEXT_SIZE;

    rect = GraphicsManager::DrawUIBox(
        GraphicsManager::WindowWidth() / 2 - GraphicsManager::WindowWidth() / 4,
        GraphicsManager::WindowHeight() / 2 - GraphicsManager::WindowHeight() / 4,
        stringLength + TEXT_PADDING * 2,
        Font::fontHeight * TEXT_SIZE + TEXT_PADDING * 2);

    GraphicsManager::DrawString(rect.x + TEXT_PADDING, rect.y + TEXT_PADDING, string.c_str(), 0xFFFFFFFF);

    rect = GraphicsManager::DrawUIBox(
        rect.x,
        rect.y + Font::fontHeight * TEXT_SIZE + TEXT_PADDING * 2 + UI_BOX_BORDER_SIZE * 3,
        stringLength + TEXT_PADDING * 2,
        TEXT_PADDING * 2 + Font::fontHeight * TEXT_SIZE * mPartyMenuIndexOptions + TEXT_PADDING * (mPartyMenuIndexOptions - 1)
    );

    GraphicsManager::DrawString(rect.x + TEXT_PADDING, rect.y + TEXT_PADDING + Font::fontHeight * TEXT_SIZE * 0, "Party", 0xFFFFFFFF);
    GraphicsManager::DrawString(rect.x + TEXT_PADDING, rect.y + TEXT_PADDING * 2 + Font::fontHeight * TEXT_SIZE * 1, "Status", 0xFFFFFFFF);
    GraphicsManager::DrawString(rect.x + TEXT_PADDING, rect.y + TEXT_PADDING * 3 + Font::fontHeight * TEXT_SIZE * 2, "Inventory", 0xFFFFFFFF);
    GraphicsManager::DrawString(rect.x + TEXT_PADDING, rect.y + TEXT_PADDING * 4 + Font::fontHeight * TEXT_SIZE * 3, "Equip", 0xFFFFFFFF);
    GraphicsManager::DrawString(rect.x + TEXT_PADDING, rect.y + TEXT_PADDING * 5 + Font::fontHeight * TEXT_SIZE * 4, "Magic", 0xFFFFFFFF);
    GraphicsManager::DrawString(rect.x + TEXT_PADDING, rect.y + TEXT_PADDING * 6 + Font::fontHeight * TEXT_SIZE * 5, "Exit", 0xFFFFFFFF);

    GraphicsManager::DrawUISelector(
        rect.x,
        rect.y + TEXT_PADDING - TEXT_PADDING / 2 + Font::fontHeight * TEXT_SIZE * mPartyMenuIndex + TEXT_PADDING * mPartyMenuIndex,
        rect.w,
        Font::fontHeight * TEXT_SIZE + TEXT_PADDING);
}