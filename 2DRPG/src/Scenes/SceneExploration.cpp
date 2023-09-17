#include "SceneExploration.h"

SceneExploration::SceneExploration()
{
    
}

SceneExploration::~SceneExploration()
{
}

void SceneExploration::Setup(SDL_Renderer* renderer)
{
    // Get level tilemap
    std::string fileName = "./assets/" + mFileName + "TileMap.png";
    SDL_Surface* surface = IMG_Load(fileName.c_str());
    if (surface)
    {
        mTileMap = SDL_CreateTextureFromSurface(renderer, surface);
    }
    SDL_FreeSurface(surface);

    int i = 0;
    Vec2 spawnPosition;

    // Load level tiles, entrances and actors
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
            std::string sceneName;
            int sceneEntranceIndex;
            Vec2 sceneEntrancePosition;
            Vec2 sceneEntranceOffset;

            while (file >> type)
            {
                if (type == "Name")
                {
                    file >> sceneName >> sceneEntranceIndex;
                }
                else if (type == "Position")
                {
                    file >> sceneEntrancePosition.x >> sceneEntrancePosition.y;
                }
                else if (type == "Offset")
                {
                    file >> sceneEntranceOffset.x >> sceneEntranceOffset.y;
                    break;
                }
            }

            SceneEntrance newEntrance =
            {
                sceneEntrancePosition * TILE_SIZE,
                sceneEntranceOffset * TILE_SIZE,
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

    // Load enemy encounters
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

    if (GameManager::GetReturnToOverworld())
    {
        for (int i = 0; i < PlayerManager::GetCharacterTextures().size(); i++)
        {
            mSpawnPositions.push_back(GameManager::GetPreviousOverworldPosition(i));
            mSpawnDirections.push_back(GameManager::GetPreviousDirection(i));
        }
    }
    else
    {
        for (const SceneEntrance& entrance : mSceneEntrances)
        {
            if (entrance.sceneEntranceIndex == GameManager::GetSceneEntranceIndex())
            {
                for (int i = 0; i < PlayerManager::GetCharacterAttributes().size(); i++)
                {
                    mSpawnPositions.push_back(entrance.position + entrance.spawnOffset);
                    mSpawnDirections.push_back(entrance.spawnOffset);
                }
            }
        }
    }
}

void SceneExploration::SetupCharacters()
{
    for (int i = 0; i < PlayerManager::GetCharacterTextures().size(); i++)
    {
        CharacterExploration newCharacter;
        newCharacter.Setup(i, mSpawnPositions[i], mSpawnDirections[i]);

        mCharacters.push_back(newCharacter);
    }
}

void SceneExploration::Shutdown()
{
    SDL_DestroyTexture(mTileMap);
}

void SceneExploration::Input()
{
    if (InputManager::UpPressed())
    {
        switch (mExplorationState)
        {
            case ES_EXPLORING:
            {
                break;
            }
            case ES_INTERACTING:
            {
                break;
            }
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
            case ES_EXPLORING:
            {
                break;
            }
            case ES_INTERACTING:
            {
                break;
            }
            case ES_MENUING:
            {
                mPartyMenuIndex++;
                if (mPartyMenuIndex >= mPartyMenuIndexOptions) mPartyMenuIndex = 0;
                break;
            }
        }
    }

    if (InputManager::OPressed())
    {
        switch (mExplorationState)
        {
            case ES_EXPLORING:
            {
                mExplorationState = ES_MENUING;
                break;
            }
            case ES_INTERACTING:
            {
                break;
            }
            case ES_MENUING:
            {
                break;
            }
        }
    }

    if (InputManager::EPressed())
    {
        switch (mExplorationState)
        {
            case ES_EXPLORING:
            {
                break;
            }
            case ES_INTERACTING:
            {
                break;
            }
            case ES_MENUING:
            {
                if (mPartyMenuIndex == mPartyMenuIndexOptions - 1) mExplorationState = ES_EXPLORING;
                break;
            }
        }
    }
}

void SceneExploration::Update(const float dt)
{
    if (mExplorationState == ES_MENUING) return;

    for (Actor& actor : mActors)
    {
        actor.UpdateAnimation();
        actor.Update(dt);
    }

    for (CharacterExploration& character : mCharacters)
    {
        character.UpdateMovement(mMapWidth, mMapHeight, mTiles, mCharacters, dt);
        character.Update(dt);

        if (character.mMovement.stepTaken && character.mPartyIndex == 0)
        {
            for (const SceneEntrance& entrance : mSceneEntrances)
            {
                if (entrance.position == character.GetPosition())
                {
                    GameManager::SetSceneToLoad(entrance.scene, entrance.sceneEntranceIndex);
                }
            }

            mStepsUntilEncounter--;
            if (mStepsUntilEncounter <= 0)
            {
                GameManager::ClearPositionsAndDirections();
                for (CharacterExploration& character : mCharacters)
                {
                    GameManager::SetPreviousOverworldPosition(character.GetPosition());
                    GameManager::SetPreviousDirection(character.mRigidbody.lastVelocity);
                }

                GameManager::SetSceneToLoad(BATTLE, -1, true, FOREST, mEnemyEncounters);
            }
        }
    }
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

    for (Actor& actor : mActors)
    {
        actor.Render(renderer);
    }

    for (int i = mCharacters.size() - 1; i >= 0; i--)
    {
        if (i == 0)
        {
            camera.x = mCharacters[i].GetPosition().x * TILE_SPRITE_SCALE - (GraphicsManager::WindowWidth() / 2);
            camera.y = mCharacters[i].GetPosition().y * TILE_SPRITE_SCALE - (GraphicsManager::WindowHeight() / 2);

            camera.x = Clampf(camera.x, 0, mMapWidth * TILE_SIZE * TILE_SPRITE_SCALE - camera.w);
            camera.y = Clampf(camera.y, 0, mMapHeight * TILE_SIZE * TILE_SPRITE_SCALE - camera.h);
        }

        mCharacters[i].Render(renderer);
    }

    if (mExplorationState == ES_MENUING)
    {
        DrawPartyMenu(renderer);
    }
}

void SceneExploration::DrawPartyMenu(SDL_Renderer* renderer)
{
    SDL_Rect firstRect;
    std::string string;

    string = std::to_string(PlayerManager::GetPartyMoney()) + 'g';

    int stringLength = 9 * Font::fontWidth * TEXT_SIZE + Font::fontSpacing * 9 * TEXT_SIZE;

    firstRect = GraphicsManager::DrawUIBox(
        GraphicsManager::WindowWidth() / 2 - GraphicsManager::WindowWidth() / 4,
        GraphicsManager::WindowHeight() / 2 - GraphicsManager::WindowHeight() / 4,
        stringLength + TEXT_PADDING * 2,
        Font::fontHeight * TEXT_SIZE + TEXT_PADDING * 2);

    GraphicsManager::DrawString(firstRect.x + TEXT_PADDING, firstRect.y + TEXT_PADDING, string.c_str());

    SDL_Rect optionsRect;
    optionsRect = GraphicsManager::DrawUIBox(
        firstRect.x,
        firstRect.y + Font::fontHeight * TEXT_SIZE + TEXT_PADDING * 2 + UI_BOX_BORDER_SIZE * 3,
        stringLength + TEXT_PADDING * 2,
        TEXT_PADDING * 2 + Font::fontHeight * TEXT_SIZE * mPartyMenuIndexOptions + TEXT_PADDING * (mPartyMenuIndexOptions - 1));

    GraphicsManager::DrawString(optionsRect.x + TEXT_PADDING, optionsRect.y + TEXT_PADDING + Font::fontHeight * TEXT_SIZE * 0, "Party");
    GraphicsManager::DrawString(optionsRect.x + TEXT_PADDING, optionsRect.y + TEXT_PADDING * 2 + Font::fontHeight * TEXT_SIZE * 1, "Status");
    GraphicsManager::DrawString(optionsRect.x + TEXT_PADDING, optionsRect.y + TEXT_PADDING * 3 + Font::fontHeight * TEXT_SIZE * 2, "Inventory");
    GraphicsManager::DrawString(optionsRect.x + TEXT_PADDING, optionsRect.y + TEXT_PADDING * 4 + Font::fontHeight * TEXT_SIZE * 3, "Equip");
    GraphicsManager::DrawString(optionsRect.x + TEXT_PADDING, optionsRect.y + TEXT_PADDING * 5 + Font::fontHeight * TEXT_SIZE * 4, "Magic");
    GraphicsManager::DrawString(optionsRect.x + TEXT_PADDING, optionsRect.y + TEXT_PADDING * 6 + Font::fontHeight * TEXT_SIZE * 5, "Exit");

    GraphicsManager::DrawUISelector(
        optionsRect.x,
        optionsRect.y + TEXT_PADDING - TEXT_PADDING / 2 + Font::fontHeight * TEXT_SIZE * mPartyMenuIndex + TEXT_PADDING * mPartyMenuIndex,
        optionsRect.w,
        Font::fontHeight * TEXT_SIZE + TEXT_PADDING);

    firstRect = GraphicsManager::DrawUIBox(
        firstRect.x + firstRect.w + UI_BOX_BORDER_SIZE * 3,
        firstRect.y,
        Font::fontWidth * TEXT_SIZE * 36 + Font::fontSpacing * TEXT_SIZE * 36 + TEXT_PADDING * 2,
        firstRect.h + optionsRect.h + UI_BOX_BORDER_SIZE * 3);

    for (int i = 0; i < PlayerManager::GetCharacterAttributes().size(); i++)
    {
        int characterXOffset = (Font::fontWidth * TEXT_SIZE * 20 + Font::fontSpacing * TEXT_SIZE * 20) * mCharacterUIPositions[i].x;
        int characterYOffset = (Font::fontHeight * TEXT_SIZE + TEXT_PADDING) * 3 * mCharacterUIPositions[i].y;

        const CharacterAttributes& attributes = PlayerManager::GetCharacterAttributes()[i];

        string = attributes.characterName + "  " + GetClassName(attributes.characterClass);

        GraphicsManager::DrawString(
            firstRect.x + TEXT_PADDING + characterXOffset,
            firstRect.y + TEXT_PADDING + characterYOffset,
            string.c_str());

        string =
            "Lv." + std::to_string(attributes.level) + ' ' + "Next Lv." + std::to_string(129);

        GraphicsManager::DrawString(
            firstRect.x + TEXT_PADDING + characterXOffset,
            firstRect.y + TEXT_PADDING + Font::fontHeight * TEXT_SIZE + TEXT_PADDING + characterYOffset,
            string.c_str());

        string =
            std::to_string(attributes.health) + '/' + std::to_string(attributes.healthMax) + "HP " +
            std::to_string(attributes.magic) + '/' + std::to_string(attributes.magicMax) + "MP";

        GraphicsManager::DrawString(
            firstRect.x + TEXT_PADDING + characterXOffset,
            firstRect.y + TEXT_PADDING + Font::fontHeight * TEXT_SIZE * 2 + TEXT_PADDING * 2 + characterYOffset,
            string.c_str());
    }
}