#include "SceneExploration.h"

SceneExploration::SceneExploration()
{
    // Interact Menu Main
    mInteractMenu.mTalkButton.OnUpAction = [this]()
    {
        mInteractMenu.SetCurrentButton(& mInteractMenu.mLeaveButton);
    };
    mInteractMenu.mTalkButton.OnDownAction = [this]()
    {
        mInteractMenu.SetCurrentButton(&mInteractMenu.mAskButton);
    };
    mInteractMenu.mTalkButton.OnAcceptAction = [this]()
    {
        mExplorationState = ES_TALKING;
    };
    mInteractMenu.mTalkButton.OnCancelAction = [this]()
    {
        mInteractMenu.SetCurrentButton(&mInteractMenu.mTalkButton);
        ClearInteractedActor();
        mExplorationState = ES_EXPLORING;
    };

    mInteractMenu.mAskButton.OnUpAction = [this]()
    {
        mInteractMenu.SetCurrentButton(&mInteractMenu.mTalkButton);
    };
    mInteractMenu.mAskButton.OnDownAction = [this]()
    {
        mInteractMenu.SetCurrentButton(&mInteractMenu.mLeaveButton);
    };
    mInteractMenu.mAskButton.OnAcceptAction = [this]()
    {
        mInteractMenu.mAskingPanel.mIsActive = true;
        mInteractMenu.mKeywordsPanel.mIsActive = true;
        mInteractMenu.SetCurrentButton(&mInteractMenu.mPeopleButton);
        mInteractMenu.CurrentButtonSelect();
    };
    mInteractMenu.mAskButton.OnCancelAction = [this]()
    {
        mInteractMenu.SetCurrentButton(&mInteractMenu.mTalkButton);
        ClearInteractedActor();
        mExplorationState = ES_EXPLORING;
    };

    mInteractMenu.mLeaveButton.OnUpAction = [this]()
    {
        mInteractMenu.SetCurrentButton(&mInteractMenu.mAskButton);
    };
    mInteractMenu.mLeaveButton.OnDownAction = [this]()
    {
        mInteractMenu.SetCurrentButton(&mInteractMenu.mTalkButton);
    };
    mInteractMenu.mLeaveButton.OnAcceptAction = [this]()
    {
        mInteractMenu.SetCurrentButton(&mInteractMenu.mTalkButton);
        ClearInteractedActor();
        mExplorationState = ES_EXPLORING;
    };
    mInteractMenu.mLeaveButton.OnCancelAction = [this]()
    {
        mInteractMenu.SetCurrentButton(&mInteractMenu.mTalkButton);
        ClearInteractedActor();
        mExplorationState = ES_EXPLORING;
    };

    // Interact Menu Ask option buttons
    mInteractMenu.mPeopleButton.OnSelected = [this]()
    {
        mInteractMenu.FillKeywordPanel(MenuInteract::PEOPLE);
    };
    mInteractMenu.mPeopleButton.OnRightAction = [this]()
    {
        mInteractMenu.SetCurrentButton(&mInteractMenu.mPlacesButton);
        mInteractMenu.CurrentButtonSelect();
    };
    mInteractMenu.mPeopleButton.OnLeftAction = [this]()
    {
        mInteractMenu.SetCurrentButton(&mInteractMenu.mBestiaryButton);
        mInteractMenu.CurrentButtonSelect();
    };
    mInteractMenu.mPeopleButton.OnAcceptAction = [this]()
    {
        if (mInteractMenu.mFirstButton.mIsActive)
        {
            mInteractMenu.SetCurrentButton(&mInteractMenu.mFirstButton);
            mInteractMenu.SetKeywordType(MenuInteract::PEOPLE);
        }

        mInteractMenu.SetPreviousButton(&mInteractMenu.mPeopleButton);
    };
    mInteractMenu.mPeopleButton.OnCancelAction = [this]()
    {
        mInteractMenu.SetCurrentButton(&mInteractMenu.mAskButton);

        mInteractMenu.mAskingPanel.mIsActive = false;
        mInteractMenu.mKeywordsPanel.mIsActive = false;
    };

    mInteractMenu.mPlacesButton.OnSelected = [this]()
    {
        mInteractMenu.FillKeywordPanel(MenuInteract::PLACES);
    };
    mInteractMenu.mPlacesButton.OnRightAction = [this]()
    {
        mInteractMenu.SetCurrentButton(&mInteractMenu.mMysteriesButton);
        mInteractMenu.CurrentButtonSelect();
    };
    mInteractMenu.mPlacesButton.OnLeftAction = [this]()
    {
        mInteractMenu.SetCurrentButton(&mInteractMenu.mPeopleButton);
        mInteractMenu.CurrentButtonSelect();
    };
    mInteractMenu.mPlacesButton.OnAcceptAction = [this]()
    {
        if (mInteractMenu.mFirstButton.mIsActive)
        {
            mInteractMenu.SetCurrentButton(&mInteractMenu.mFirstButton);
            mInteractMenu.SetKeywordType(MenuInteract::PLACES);
        }

        mInteractMenu.SetPreviousButton(&mInteractMenu.mPlacesButton);
    };
    mInteractMenu.mPlacesButton.OnCancelAction = [this]()
    {
        mInteractMenu.SetCurrentButton(&mInteractMenu.mAskButton);

        mInteractMenu.mAskingPanel.mIsActive = false;
        mInteractMenu.mKeywordsPanel.mIsActive = false;
    };

    mInteractMenu.mMysteriesButton.OnSelected = [this]()
    {
        mInteractMenu.FillKeywordPanel(MenuInteract::MYSTERIES);
    };
    mInteractMenu.mMysteriesButton.OnRightAction = [this]()
    {
        mInteractMenu.SetCurrentButton(&mInteractMenu.mBestiaryButton);
        mInteractMenu.CurrentButtonSelect();
    };
    mInteractMenu.mMysteriesButton.OnLeftAction = [this]()
    {
        mInteractMenu.SetCurrentButton(&mInteractMenu.mPlacesButton);
        mInteractMenu.CurrentButtonSelect();
    };
    mInteractMenu.mMysteriesButton.OnAcceptAction = [this]()
    {
        if (mInteractMenu.mFirstButton.mIsActive)
        {
            mInteractMenu.SetCurrentButton(&mInteractMenu.mFirstButton);
            mInteractMenu.SetKeywordType(MenuInteract::MYSTERIES);
        }

        mInteractMenu.SetPreviousButton(&mInteractMenu.mMysteriesButton);
    };
    mInteractMenu.mMysteriesButton.OnCancelAction = [this]()
    {
        mInteractMenu.SetCurrentButton(&mInteractMenu.mAskButton);

        mInteractMenu.mAskingPanel.mIsActive = false;
        mInteractMenu.mKeywordsPanel.mIsActive = false;
    };

    mInteractMenu.mBestiaryButton.OnSelected = [this]()
    {
        mInteractMenu.FillKeywordPanel(MenuInteract::BESTIARY);
    };
    mInteractMenu.mBestiaryButton.OnRightAction = [this]()
    {
        mInteractMenu.SetCurrentButton(&mInteractMenu.mPeopleButton);
        mInteractMenu.CurrentButtonSelect();
    };
    mInteractMenu.mBestiaryButton.OnLeftAction = [this]()
    {
        mInteractMenu.SetCurrentButton(&mInteractMenu.mMysteriesButton);
        mInteractMenu.CurrentButtonSelect();
    };
    mInteractMenu.mBestiaryButton.OnAcceptAction = [this]()
    {
        if (mInteractMenu.mFirstButton.mIsActive)
        {
            mInteractMenu.SetCurrentButton(&mInteractMenu.mFirstButton);
            mInteractMenu.SetKeywordType(MenuInteract::BESTIARY);
        }

        mInteractMenu.SetPreviousButton(&mInteractMenu.mBestiaryButton);
    };
    mInteractMenu.mBestiaryButton.OnCancelAction = [this]()
    {
        mInteractMenu.SetCurrentButton(&mInteractMenu.mAskButton);

        mInteractMenu.mAskingPanel.mIsActive = false;
        mInteractMenu.mKeywordsPanel.mIsActive = false;
    };

    // Keyword Buttons
    mInteractMenu.mFirstButton.OnRightAction = [this]()
    {
        if (mInteractMenu.mSecondButton.mIsActive)
        {
            mInteractMenu.SetCurrentButton(&mInteractMenu.mSecondButton);
        }
    };
    mInteractMenu.mFirstButton.OnDownAction = [this]()
    {
        if (mInteractMenu.mThirdButton.mIsActive)
        {
            mInteractMenu.SetCurrentButton(&mInteractMenu.mThirdButton);
        }
    };
    mInteractMenu.mFirstButton.OnAcceptAction = [this]()
    {
        AskAboutKeyword(0);
    };
    mInteractMenu.mFirstButton.OnCancelAction = [this]()
    {
        mInteractMenu.SetCurrentButton(mInteractMenu.GetPreviousButton());
    };

    mInteractMenu.mSecondButton.OnLeftAction = [this]()
    {
        if (mInteractMenu.mFirstButton.mIsActive)
        {
            mInteractMenu.SetCurrentButton(&mInteractMenu.mFirstButton);
        }
    };
    mInteractMenu.mSecondButton.OnDownAction = [this]()
    {
        if (mInteractMenu.mFourthButton.mIsActive)
        {
            mInteractMenu.SetCurrentButton(&mInteractMenu.mFourthButton);
        }
    };
    mInteractMenu.mSecondButton.OnCancelAction = [this]()
    {
        mInteractMenu.SetCurrentButton(mInteractMenu.GetPreviousButton());
    };

    mInteractMenu.mThirdButton.OnUpAction = [this]()
    {
        if (mInteractMenu.mFirstButton.mIsActive)
        {
            mInteractMenu.SetCurrentButton(&mInteractMenu.mFirstButton);
        }
    };
    mInteractMenu.mThirdButton.OnRightAction = [this]()
    {
        if (mInteractMenu.mFourthButton.mIsActive)
        {
            mInteractMenu.SetCurrentButton(&mInteractMenu.mFourthButton);
        }
    };
    mInteractMenu.mThirdButton.OnDownAction = [this]()
    {
        if (mInteractMenu.mFifthButton.mIsActive)
        {
            mInteractMenu.SetCurrentButton(&mInteractMenu.mFifthButton);
        }
    };
    mInteractMenu.mThirdButton.OnCancelAction = [this]()
    {
        mInteractMenu.SetCurrentButton(mInteractMenu.GetPreviousButton());
    };

    mInteractMenu.mFourthButton.OnUpAction = [this]()
    {
        if (mInteractMenu.mSecondButton.mIsActive)
        {
            mInteractMenu.SetCurrentButton(&mInteractMenu.mSecondButton);
        }
    };
    mInteractMenu.mFourthButton.OnLeftAction = [this]()
    {
        if (mInteractMenu.mThirdButton.mIsActive)
        {
            mInteractMenu.SetCurrentButton(&mInteractMenu.mThirdButton);
        }
    };
    mInteractMenu.mFourthButton.OnDownAction = [this]()
    {
        if (mInteractMenu.mSixthButton.mIsActive)
        {
            mInteractMenu.SetCurrentButton(&mInteractMenu.mSixthButton);
        }
    };
    mInteractMenu.mFourthButton.OnCancelAction = [this]()
    {
        mInteractMenu.SetCurrentButton(mInteractMenu.GetPreviousButton());
    };

    mInteractMenu.mFifthButton.OnUpAction = [this]()
    {
        if (mInteractMenu.mThirdButton.mIsActive)
        {
            mInteractMenu.SetCurrentButton(&mInteractMenu.mThirdButton);
        }
    };
    mInteractMenu.mFifthButton.OnRightAction = [this]()
    {
        if (mInteractMenu.mSixthButton.mIsActive)
        {
            mInteractMenu.SetCurrentButton(&mInteractMenu.mSixthButton);
        }
    };
    mInteractMenu.mFifthButton.OnDownAction = [this]()
    {
        
    };
    mInteractMenu.mFifthButton.OnCancelAction = [this]()
    {
        mInteractMenu.SetCurrentButton(mInteractMenu.GetPreviousButton());
    };

    mInteractMenu.mSixthButton.OnUpAction = [this]()
    {
        if (mInteractMenu.mFourthButton.mIsActive)
        {
            mInteractMenu.SetCurrentButton(&mInteractMenu.mFourthButton);
        }
    };
    mInteractMenu.mSixthButton.OnLeftAction = [this]()
    {
        if (mInteractMenu.mFifthButton.mIsActive)
        {
            mInteractMenu.SetCurrentButton(&mInteractMenu.mFifthButton);
        }
    };
    mInteractMenu.mSixthButton.OnDownAction = [this]()
    {
        
    };
    mInteractMenu.mSixthButton.OnCancelAction = [this]()
    {
        mInteractMenu.SetCurrentButton(mInteractMenu.GetPreviousButton());
    };

    // Party Menu Buttons
    mPartyMenu.mPartyButton.OnCancelAction = [this]()
    {
        mExplorationState = ES_EXPLORING;
    };
    mPartyMenu.mStatusButton.OnCancelAction = [this]()
    {
        mExplorationState = ES_EXPLORING;
    };
    mPartyMenu.mInventoryButton.OnCancelAction = [this]()
    {
        mExplorationState = ES_EXPLORING;
    };
    mPartyMenu.mJournalButton.OnCancelAction = [this]()
    {
        mExplorationState = ES_EXPLORING;
    };
    mPartyMenu.mEquipButton.OnCancelAction = [this]()
    {
        mExplorationState = ES_EXPLORING;
    };
    mPartyMenu.mMagicButton.OnCancelAction = [this]()
    {
        mExplorationState = ES_EXPLORING;
    };
    mPartyMenu.mExitButton.OnCancelAction = [this]()
    {
        mExplorationState = ES_EXPLORING;
    };

    // Party
    mPartyMenu.mFirstCharacterButton.OnAcceptAction = [this]()
    {
        if (mPartyMenu.mCharacterSelected && mPartyMenu.mFirstCharacterIndex != 0)
        {
            PlayerManager::SwapCharacters(mPartyMenu.mFirstCharacterIndex, 0);
            mPartyMenu.FillPartyAttributes();
            mPartyMenu.mCharacterSelected = false;

            SwapCharacters(mPartyMenu.mFirstCharacterIndex, 0);
        }
        else
        {
            mPartyMenu.mFirstCharacterIndex = 0;
            mPartyMenu.mCharacterSelected = true;
        }
    };
    mPartyMenu.mSecondCharacterButton.OnAcceptAction = [this]()
    {
        if (mPartyMenu.mCharacterSelected && mPartyMenu.mFirstCharacterIndex != 1)
        {
            PlayerManager::SwapCharacters(mPartyMenu.mFirstCharacterIndex, 1);
            mPartyMenu.FillPartyAttributes();
            mPartyMenu.mCharacterSelected = false;

            SwapCharacters(mPartyMenu.mFirstCharacterIndex, 1);
        }
        else
        {
            mPartyMenu.mFirstCharacterIndex = 1;
            mPartyMenu.mCharacterSelected = true;
        }
    };
    mPartyMenu.mThirdCharacterButton.OnAcceptAction = [this]()
    {
        if (mPartyMenu.mCharacterSelected && mPartyMenu.mFirstCharacterIndex != 2)
        {
            PlayerManager::SwapCharacters(mPartyMenu.mFirstCharacterIndex, 2);
            mPartyMenu.FillPartyAttributes();
            mPartyMenu.mCharacterSelected = false;

            SwapCharacters(mPartyMenu.mFirstCharacterIndex, 2);
        }
        else
        {
            mPartyMenu.mFirstCharacterIndex = 2;
            mPartyMenu.mCharacterSelected = true;
        }
    };
    mPartyMenu.mFourthCharacterButton.OnAcceptAction = [this]()
    {
        if (mPartyMenu.mCharacterSelected && mPartyMenu.mFirstCharacterIndex != 3)
        {
            PlayerManager::SwapCharacters(mPartyMenu.mFirstCharacterIndex, 3);
            mPartyMenu.FillPartyAttributes();
            mPartyMenu.mCharacterSelected = false;

            SwapCharacters(mPartyMenu.mFirstCharacterIndex, 3);
        }
        else
        {
            mPartyMenu.mFirstCharacterIndex = 3;
            mPartyMenu.mCharacterSelected = true;
        }
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

    // Load menu icons
    surface = IMG_Load(mBattleIconsFilePath.c_str());
    if (surface)
    {
        mBattleIconsTexture = SDL_CreateTextureFromSurface(renderer, surface);
    }
    SDL_FreeSurface(surface);

    std::ifstream battleIconsFile("./assets/BattleIcons.txt");
    while (battleIconsFile >> type)
    {
        if (type == "Cursor")
        {
            Sprite newSprite;

            battleIconsFile >> newSprite.srcRect.x >> newSprite.srcRect.y >> newSprite.srcRect.w >> newSprite.srcRect.h;
            mBattleIconsMap.emplace("Cursor", newSprite);
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

void SceneExploration::AskAboutKeyword(int index)
{
    if (mInteractedActor)
    {
        switch (mInteractMenu.GetKeywordType())
        {
            case MenuInteract::PEOPLE:
            {
                if (mInteractedActor->HasAnswerToKeyword(PlayerManager::GetPeopleKeywords()[index]))
                {
                    mInteractedActor->SetAnswerKey(PlayerManager::GetPeopleKeywords()[index]);
                    mInteractedActor->SetDialogueMode(ED_ANSWER);
                    mExplorationState = ES_TALKING;
                }
                break;
            }
            case MenuInteract::PLACES:
            {
                if (mInteractedActor->HasAnswerToKeyword(PlayerManager::GetPlacesKeywords()[index]))
                {
                    mInteractedActor->SetAnswerKey(PlayerManager::GetPlacesKeywords()[index]);
                    mInteractedActor->SetDialogueMode(ED_ANSWER);
                    mExplorationState = ES_TALKING;
                }
                break;
            }
            case MenuInteract::MYSTERIES:
            {
                if (mInteractedActor->HasAnswerToKeyword(PlayerManager::GetMysteryKeywords()[index]))
                {
                    mInteractedActor->SetAnswerKey(PlayerManager::GetMysteryKeywords()[index]);
                    mInteractedActor->SetDialogueMode(ED_ANSWER);
                    mExplorationState = ES_TALKING;
                }
                break;
            }
            case MenuInteract::BESTIARY:
            {
                if (mInteractedActor->HasAnswerToKeyword(PlayerManager::GetBestiaryKeywords()[index]))
                {
                    mInteractedActor->SetAnswerKey(PlayerManager::GetBestiaryKeywords()[index]);
                    mInteractedActor->SetDialogueMode(ED_ANSWER);
                    mExplorationState = ES_TALKING;
                }
                break;
            }
        }
        
    }
}

void SceneExploration::SwapCharacters(int first, int second)
{
    SDL_Texture* temp = mCharacters[first].mSpriteSheet;
    mCharacters[first].mSpriteSheet = mCharacters[second].mSpriteSheet;
    mCharacters[second].mSpriteSheet = temp;

    std::map<std::string, Animation> tempAnims = mCharacters[first].mAnimations;
    mCharacters[first].mAnimations = mCharacters[second].mAnimations;
    mCharacters[second].mAnimations = tempAnims;

    std::string tempAnim = mCharacters[first].mCurrentAnimation;
    mCharacters[first].mCurrentAnimation = mCharacters[second].mCurrentAnimation;
    mCharacters[second].mCurrentAnimation = tempAnim;
}

void SceneExploration::Shutdown()
{
    for (Actor& actor : mActors)
    {
        actor.DestroySpriteSheet();
    }
    ClearInteractedActor();
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
            
            if (InputManager::StartPressed())
            {
                mExplorationState = ES_MENUING;
            }
            break;
        }
        case ES_INTERACTING:
        {
            if (InputManager::UpPressed() && mInteractMenu.GetCurrentButton()->OnUpAction)
            {
                mInteractMenu.GetCurrentButton()->OnUpAction();
            }
            else if (InputManager::DownPressed() && mInteractMenu.GetCurrentButton()->OnDownAction)
            {
                mInteractMenu.GetCurrentButton()->OnDownAction();
            }
            else if (InputManager::RightPressed() && mInteractMenu.GetCurrentButton()->OnRightAction)
            {
                mInteractMenu.GetCurrentButton()->OnRightAction();
            }
            else if (InputManager::LeftPressed() && mInteractMenu.GetCurrentButton()->OnLeftAction)
            {
                mInteractMenu.GetCurrentButton()->OnLeftAction();
            }
            else if (InputManager::AcceptPressed() && mInteractMenu.GetCurrentButton()->OnAcceptAction)
            {
                mInteractMenu.GetCurrentButton()->OnAcceptAction();
            }
            else if (InputManager::CancelPressed() && mInteractMenu.GetCurrentButton()->OnCancelAction)
            {
                mInteractMenu.GetCurrentButton()->OnCancelAction();
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
                                    break;
                                }
                                case EJ_BESTIARY:
                                {
                                    PlayerManager::LearnNewBestiaryKeyword(mInteractedActor->GetKeyword());
                                    break;
                                }
                            }
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
            break;
        }
        case ES_MENUING:
        {
            if (InputManager::UpPressed() && mPartyMenu.GetCurrentButton()->OnUpAction)
            {
                mPartyMenu.GetCurrentButton()->OnUpAction();
            }
            else if (InputManager::DownPressed() && mPartyMenu.GetCurrentButton()->OnDownAction)
            {
                mPartyMenu.GetCurrentButton()->OnDownAction();
            }
            else if (InputManager::RightPressed() && mPartyMenu.GetCurrentButton()->OnRightAction)
            {
                mPartyMenu.GetCurrentButton()->OnRightAction();
            }
            else if (InputManager::LeftPressed() && mPartyMenu.GetCurrentButton()->OnLeftAction)
            {
                mPartyMenu.GetCurrentButton()->OnLeftAction();
            }
            else if (InputManager::AcceptPressed() && mPartyMenu.GetCurrentButton()->OnAcceptAction)
            {
                mPartyMenu.GetCurrentButton()->OnAcceptAction();
            }
            else if (InputManager::CancelPressed())
            {
                if (mPartyMenu.GetCurrentButton()->OnCancelAction)
                {
                    mPartyMenu.GetCurrentButton()->OnCancelAction();
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
    // Render tiles
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
            mTiles[i].position.x * TILE_SPRITE_SCALE - GraphicsManager::GetCamera().x,
            mTiles[i].position.y * TILE_SPRITE_SCALE - GraphicsManager::GetCamera().y,
            TILE_SIZE * TILE_SPRITE_SCALE,
            TILE_SIZE * TILE_SPRITE_SCALE
        };

        GraphicsManager::DrawSpriteRect(mTileMap, srcRect, destRect);
    }

    /*for (int y = 0; y < mMapHeight; y++)
    {
        for (int x = 0; x < mMapWidth; x++)
        {
            SDL_Rect& camera = GraphicsManager::Camera();
            float xMod = camera.x % TILE_SIZE * TILE_SPRITE_SCALE;
            float yMod = camera.y % TILE_SIZE * TILE_SPRITE_SCALE;

            Vec2 cameraPosition;
            cameraPosition.x = camera.x - xMod;
            cameraPosition.y = camera.y - yMod;

            if (
                x * TILE_SIZE * TILE_SPRITE_SCALE < cameraPosition.x || x * TILE_SIZE * TILE_SPRITE_SCALE >= cameraPosition.x + camera.w ||
                y * TILE_SIZE * TILE_SPRITE_SCALE < cameraPosition.y || y * TILE_SIZE * TILE_SPRITE_SCALE >= cameraPosition.y + camera.h)
                continue;

            int index = x + y * mMapWidth;

            SDL_Rect srcRect =
            {
                mTiles[index].spriteIndex % SPRITE_SHEET_SIZE * TILE_SIZE,
                mTiles[index].spriteIndex / SPRITE_SHEET_SIZE * TILE_SIZE,
                TILE_SIZE,
                TILE_SIZE
            };

            SDL_Rect destRect =
            {
                mTiles[index].position.x * TILE_SPRITE_SCALE - GraphicsManager::Camera().x,
                mTiles[index].position.y * TILE_SPRITE_SCALE - GraphicsManager::Camera().y,
                TILE_SIZE * TILE_SPRITE_SCALE,
                TILE_SIZE * TILE_SPRITE_SCALE
            };

            GraphicsManager::DrawSpriteRect(mTileMap, srcRect, destRect);
        }
    }*/

    // Render Actors
    for (Actor& actor : mActors)
    {
        actor.Render(renderer);
    }

    // Render Party Characters
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

    // Render switch
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
            DrawCursor(renderer);
            break;
        }
    }
}

void SceneExploration::DrawCursor(SDL_Renderer* renderer)
{
    SDL_Rect& cursorSpriteRect = mBattleIconsMap.at("Cursor").srcRect;

    SDL_Rect destRect =
    {
        mPartyMenu.GetCurrentButton()->mPosition.x - cursorSpriteRect.w * BATTLE_CURSOR_SCALE - 5,
        mPartyMenu.GetCurrentButton()->mPosition.y,
        cursorSpriteRect.w * BATTLE_CURSOR_SCALE,
        cursorSpriteRect.h * BATTLE_CURSOR_SCALE
    };

    GraphicsManager::DrawSpriteRect(mBattleIconsTexture, cursorSpriteRect, destRect);
}