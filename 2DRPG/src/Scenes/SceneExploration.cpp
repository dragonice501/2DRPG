#include "SceneExploration.h"

SceneExploration::SceneExploration()
{
    mInteractMenu.mTalkButton.OnSelected = [this]()
    {
        mInteractMenu.mMainButtonIndex = 0;
    };
    mInteractMenu.mTalkButton.OnUpAction = [this]()
    {
        mInteractMenu.SetCurrentButton(& mInteractMenu.mLeaveButton);
        mInteractMenu.GetCurrentButton().OnSelected();
    };
    mInteractMenu.mTalkButton.OnDownAction = [this]()
    {
        mInteractMenu.SetCurrentButton(&mInteractMenu.mAskButton);
        mInteractMenu.GetCurrentButton().OnSelected();
    };
    mInteractMenu.mTalkButton.OnAcceptAction = [this]()
    {
        mExplorationState = ES_TALKING;
    };

    mInteractMenu.mAskButton.OnSelected = [this]()
    {
        mInteractMenu.mMainButtonIndex = 1;
    };
    mInteractMenu.mAskButton.OnUpAction = [this]()
    {
        mInteractMenu.SetCurrentButton(&mInteractMenu.mTalkButton);
        mInteractMenu.GetCurrentButton().OnSelected();
    };
    mInteractMenu.mAskButton.OnDownAction = [this]()
    {
        mInteractMenu.SetCurrentButton(&mInteractMenu.mLeaveButton);
        mInteractMenu.GetCurrentButton().OnSelected();
    };
    mInteractMenu.mAskButton.OnAcceptAction = [this]()
    {
        
    };

    mInteractMenu.mLeaveButton.OnSelected = [this]()
    {
        mInteractMenu.mMainButtonIndex = 2;
    };
    mInteractMenu.mLeaveButton.OnUpAction = [this]()
    {
        mInteractMenu.SetCurrentButton(&mInteractMenu.mAskButton);
        mInteractMenu.GetCurrentButton().OnSelected();
    };
    mInteractMenu.mLeaveButton.OnDownAction = [this]()
    {
        mInteractMenu.SetCurrentButton(&mInteractMenu.mTalkButton);
        mInteractMenu.GetCurrentButton().OnSelected();
    };
    mInteractMenu.mLeaveButton.OnAcceptAction = [this]()
    {
        mInteractMenu.SetCurrentButton(&mInteractMenu.mTalkButton);
        mExplorationState = ES_EXPLORING;
    };

    mPartyMenu.SetCurrentButton(&mPartyMenu.mPartyButton);
    mInteractMenu.SetCurrentButton(&mInteractMenu.mTalkButton);
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

            ActorNpc newActor;
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
    switch (mExplorationState)
    {
        case ES_EXPLORING:
        {
            if (InputManager::UpHeld())
            {
                for (CharacterExploration& character : mCharacters)
                {
                    character.mMovement.upHeld = true;
                }
            }
            else
            {
                for (CharacterExploration& character : mCharacters)
                {
                    character.mMovement.upHeld = false;
                }
            }

            if (InputManager::DownHeld())
            {
                for (CharacterExploration& character : mCharacters)
                {
                    character.mMovement.downHeld = true;
                }
            }
            else
            {
                for (CharacterExploration& character : mCharacters)
                {
                    character.mMovement.downHeld = false;
                }
            }

            if (InputManager::RightHeld())
            {
                for (CharacterExploration& character : mCharacters)
                {
                    character.mMovement.rightHeld = true;
                }
            }
            else
            {
                for (CharacterExploration& character : mCharacters)
                {
                    character.mMovement.rightHeld = false;
                }
            }

            if (InputManager::LeftHeld())
            {
                for (CharacterExploration& character : mCharacters)
                {
                    character.mMovement.leftHeld = true;
                }
            }
            else
            {
                for (CharacterExploration& character : mCharacters)
                {
                    character.mMovement.leftHeld = false;
                }
            }

            if (InputManager::AcceptPressed())
            {
                for (ActorNpc& actor : mActors)
                {
                    Vec2 interactPosition = mCharacters[0].GetPosition() + mCharacters[0].mRigidbody.lastVelocity;

                    if (actor.GetPosition() == interactPosition)
                    {
                        mInteractedActor = &actor;
                        if (mInteractedActor)
                            mInteractedActor->mCurrentDialogueMode = ED_GREETING;

                        mInteractMenuIndex = 0;
                        mExplorationState = ES_INTERACTING;
                    }
                }
            }
            else if (InputManager::StartPressed())
            {
                mExplorationState = ES_MENUING;
            }
            break;
        }
        case ES_INTERACTING:
        {
            if (InputManager::UpPressed() && mInteractMenu.GetCurrentButton().OnUpAction)
            {
                mInteractMenu.GetCurrentButton().OnUpAction();
            }
            else if (InputManager::DownPressed() && mInteractMenu.GetCurrentButton().OnDownAction)
            {
                mInteractMenu.GetCurrentButton().OnDownAction();
            }
            else if (InputManager::RightPressed() && mInteractMenu.GetCurrentButton().OnRightAction)
            {
                mInteractMenu.GetCurrentButton().OnRightAction();
            }
            else if (InputManager::LeftPressed() && mInteractMenu.GetCurrentButton().OnLeftAction)
            {
                mInteractMenu.GetCurrentButton().OnLeftAction();
            }
            else if (InputManager::AcceptPressed() && mInteractMenu.GetCurrentButton().OnAcceptAction)
            {
                mInteractMenu.GetCurrentButton().OnAcceptAction();
            }
            else if (InputManager::CancelPressed())
            {
                if (mInteractMenu.mIsInteractMenu)
                {
                    mExplorationState = ES_EXPLORING;
                }
                else if (mInteractMenu.GetCurrentButton().OnCancelAction)
                {
                    mInteractMenu.SetCurrentButton(&mInteractMenu.mTalkButton);
                    mInteractMenu.GetCurrentButton().OnCancelAction();
                }
            }
            break;
        }
        case ES_TALKING:
        {
            if (InputManager::AcceptPressed())
            {
                if (mInteractedActor)
                {
                    if (!mInteractedActor->CycleThroughDialogue())
                    {
                        if (mInteractedActor->HasNewInformation())
                        {
                            mInteractedActor->SetDialogueMode(ED_INFORMATION);

                            switch (mInteractedActor->GetKeywordType())
                            {
                                case EJ_PERSON:
                                {
                                    PlayerManager::LearnNewPeopleKeyword(mInteractedActor->GetKeyword());
                                    break;
                                }
                                case EJ_PLACE:
                                {
                                    PlayerManager::LearnNewPlaceKeyword(mInteractedActor->GetKeyword());
                                    break;
                                }
                                case EJ_MYSTERY:
                                {
                                    PlayerManager::LearnNewMysteryKeyword(mInteractedActor->GetKeyword());
                                }
                                case EJ_BESTIARY:
                                {
                                    PlayerManager::LearnNewMysteryKeyword(mInteractedActor->GetKeyword());
                                }
                            }

                            //PlayerManager::LearnNewKeyword(mInteractedActor->GetKeyword());
                        }
                        else
                        {
                            mInteractedActor->SetDialogueMode(ED_GREETING);
                            mExplorationState = ES_INTERACTING;
                        }
                    }
                    break;
                }
            }
        }
        case ES_ASKING:
        {
            if (InputManager::UpPressed())
            {
                mAskingMenuIndex--;
                //if (mAskingMenuIndex < 0) mAskingMenuIndex = PlayerManager::GetLearnedKeywords().size() - 1;
            }
            else if (InputManager::DownPressed())
            {
                mAskingMenuIndex++;
                //if (mAskingMenuIndex >= PlayerManager::GetLearnedKeywords().size()) mAskingMenuIndex = 0;
            }
            if (InputManager::AcceptPressed())
            {
                if (mInteractedActor)
                {
                    /*if (mInteractedActor->HasAnswerToKeyword(PlayerManager::GetLearnedKeywords()[mAskingMenuIndex]))
                    {
                        mInteractedActor->SetAnswerKey(PlayerManager::GetLearnedKeywords()[mAskingMenuIndex]);
                        mInteractedActor->SetDialogueMode(ED_ANSWER);
                        mExplorationState = ES_TALKING;
                    }*/
                }
            }
            if (InputManager::CancelPressed())
            {
                mExplorationState = ES_INTERACTING;
            }
            break;
        }
        case ES_MENUING:
        {
            if (InputManager::StartPressed())
            {
                mExplorationState = ES_EXPLORING;
            }

            if (InputManager::UpPressed() && mPartyMenu.GetCurrentButton().OnUpAction)
            {
                mPartyMenu.GetCurrentButton().OnUpAction();
            }
            else if (InputManager::DownPressed() && mPartyMenu.GetCurrentButton().OnDownAction)
            {
                mPartyMenu.GetCurrentButton().OnDownAction();
            }
            else if (InputManager::RightPressed() && mPartyMenu.GetCurrentButton().OnRightAction)
            {
                mPartyMenu.GetCurrentButton().OnRightAction();
            }
            else if (InputManager::LeftPressed() && mPartyMenu.GetCurrentButton().OnLeftAction)
            {
                mPartyMenu.GetCurrentButton().OnLeftAction();
            }
            else if (InputManager::AcceptPressed() && mPartyMenu.GetCurrentButton().OnAcceptAction)
            {
                mPartyMenu.GetCurrentButton().OnAcceptAction();
            }
            else if (InputManager::CancelPressed())
            {
                if (mPartyMenu.mIsMainMenu)
                {
                    mExplorationState = ES_EXPLORING;
                }
                else if (mPartyMenu.GetCurrentButton().OnCancelAction)
                {
                    mPartyMenu.SetCurrentButton(&mPartyMenu.mPartyButton);
                    mPartyMenu.GetCurrentButton().OnCancelAction();
                }
            }
            break;
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
        character.UpdateMovement(mMapWidth, mMapHeight, mTiles, mCharacters, mActors, dt);
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

            if(GameManager::GetIsOverworld()) mStepsUntilEncounter--;

            if (mStepsUntilEncounter <= 0)
            {
                GameManager::ClearPositionsAndDirections();
                for (CharacterExploration& character : mCharacters)
                {
                    GameManager::SetPreviousOverworldPosition(character.GetPosition());
                    GameManager::SetPreviousDirection(character.mRigidbody.lastVelocity);
                }

                int terrainIndex = static_cast<int>(character.GetPosition().x) / 16 + (static_cast<int>(character.GetPosition().y) / 16) * mMapWidth;

                GameManager::SetSceneToLoad(BATTLE, -1, true, mTiles[terrainIndex].terrainType, mEnemyEncounters);
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

    switch (mExplorationState)
    {
        case ES_EXPLORING:
        {
            break;
        }
        case ES_INTERACTING:
        {
            mInteractMenu.Render(renderer);
            break;
        }
        case ES_TALKING:
        {
            SDL_Rect dialogueRect = GraphicsManager::DrawDialogueBox();
            if(mInteractedActor)
                GraphicsManager::DrawDialogue(dialogueRect, mInteractedActor->GetCurrentDialogue());
            break;
        }
        case ES_ASKING:
        {
            break;
        }
        case ES_MENUING:
        { 
            mPartyMenu.Render(renderer);
            break;
        }
    }
}
