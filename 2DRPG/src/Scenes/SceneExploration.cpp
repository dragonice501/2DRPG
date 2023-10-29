#include "SceneExploration.h"

SceneExploration::SceneExploration()
{
    // Interact Menu Main
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
    mPartyMenu.mSaveButton.OnCancelAction = [this]()
    {
        mExplorationState = ES_EXPLORING;
    };
    mPartyMenu.mExitButton.OnAcceptAction = [this]()
    {
        mExplorationState = ES_EXPLORING;
    };
    mPartyMenu.mExitButton.OnCancelAction = [this]()
    {
        mExplorationState = ES_EXPLORING;
    };

    // Party Panel
    mPartyMenu.mPartyButtonOne.OnAcceptAction = [this]()
    {
        if (mPartyMenu.mCharacterSelected && mPartyMenu.mSelectedCharacterIndex != 0)
        {
            PlayerManager::SwapCharacters(mPartyMenu.mSelectedCharacterIndex, 0);
            mPartyMenu.FillPartyAttributes();
            mPartyMenu.mCharacterSelected = false;

            SwapCharacters(mPartyMenu.mSelectedCharacterIndex, 0);
        }
        else
        {
            mPartyMenu.mSelectedCharacterIndex = 0;
            mPartyMenu.mCharacterSelected = true;
        }
    };
    mPartyMenu.mPartyButtonTwo.OnAcceptAction = [this]()
    {
        if (mPartyMenu.mCharacterSelected && mPartyMenu.mSelectedCharacterIndex != 1)
        {
            PlayerManager::SwapCharacters(mPartyMenu.mSelectedCharacterIndex, 1);
            mPartyMenu.FillPartyAttributes();
            mPartyMenu.mCharacterSelected = false;

            SwapCharacters(mPartyMenu.mSelectedCharacterIndex, 1);
        }
        else
        {
            mPartyMenu.mSelectedCharacterIndex = 1;
            mPartyMenu.mCharacterSelected = true;
        }
    };
    mPartyMenu.mPartyButtonThree.OnAcceptAction = [this]()
    {
        if (mPartyMenu.mCharacterSelected && mPartyMenu.mSelectedCharacterIndex != 2)
        {
            PlayerManager::SwapCharacters(mPartyMenu.mSelectedCharacterIndex, 2);
            mPartyMenu.FillPartyAttributes();
            mPartyMenu.mCharacterSelected = false;

            SwapCharacters(mPartyMenu.mSelectedCharacterIndex, 2);
        }
        else
        {
            mPartyMenu.mSelectedCharacterIndex = 2;
            mPartyMenu.mCharacterSelected = true;
        }
    };
    mPartyMenu.mPartyButtonFour.OnAcceptAction = [this]()
    {
        if (mPartyMenu.mCharacterSelected && mPartyMenu.mSelectedCharacterIndex != 3)
        {
            PlayerManager::SwapCharacters(mPartyMenu.mSelectedCharacterIndex, 3);
            mPartyMenu.FillPartyAttributes();
            mPartyMenu.mCharacterSelected = false;

            SwapCharacters(mPartyMenu.mSelectedCharacterIndex, 3);
        }
        else
        {
            mPartyMenu.mSelectedCharacterIndex = 3;
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
    std::string fileName;
    int i = 0;
    Vec2 spawnPosition;

    // Load level tiles, entrances and actors
    fileName = "./assets/files/" + mFileName + "SaveFile.txt";
    std::ifstream file(fileName);
    std::string type;
    while (file >> type)
    {
        if (type == "MapSize")
        {
            file >> mMapWidth >> mMapHeight;
        }
        else if (type == "MapCentered") file >> mDrawMapCentered;
        else if (type == "TileMap")
        {
            file >> mTileMapName;
        }
        else if (type == "EncounterRate")
        {
            file >> mEncounterStepsMin >> mEncounterStepsMax;
        }
        else if (type == "SceneEntrance")
        {
            std::string sceneName;
            int sceneEntranceIndex;
            int nextSceneEntrance;
            Vec2 sceneEntrancePosition;
            Vec2 sceneEntranceOffset;

            file >> sceneEntranceIndex;

            while (file >> type)
            {
                if (type == "Name")
                {
                    file >> sceneName >> nextSceneEntrance;
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
                sceneEntranceIndex,
                nextSceneEntrance
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
            mNpcs.push_back(newActor);
        }
        else if (type == "Interactable")
        {
            ActorInteractable newInteractable;
            int xPos;
            int yPos;

            file >> xPos >> yPos;

            newInteractable.mPosition = { static_cast<float>(xPos * TILE_SIZE), static_cast<float>(yPos * TILE_SIZE) };

            mInteractables.push_back(newInteractable);
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

    // Create Textures
    AssetManager::CreateTileMapTexture(mTileMapName);
    AssetManager::CreateMenuIconsTexture();

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

    // Randomize Encounter Steps
    mStepsUntilEncounter = rand() % (mEncounterStepsMax - mEncounterStepsMin + 1) + mEncounterStepsMin;
    //mStepsUntilEncounter = 1;

    // Load enemy encounters
    EnemyEncounter newEncounter;
    fileName = "./assets/files/" + mFileName + "Encounters.txt";
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
        for (int i = 0; i < PlayerManager::GetCharacterAttributes().size(); i++)
        {
            mSpawnPositions.push_back(GameManager::GetPreviousCharacterPosition(i));
            mSpawnDirections.push_back(GameManager::GetPreviousCharacterDirection(i));
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
    for (int i = 0; i < PlayerManager::GetCharacterAttributes().size(); i++)
    {
        CharacterExploration newCharacter;
        newCharacter.Setup(i, mSpawnPositions[i], mSpawnDirections[i]);

        GameManager::SetCurrentCharacterPosition(i, mSpawnPositions[i]);

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

    PlayerManager::SwapCharacterInventories(first, second);
}

void SceneExploration::Shutdown()
{
    for (ActorNpc& npc : mNpcs)
    {
        npc.DestroySpriteSheet();
    }
    ClearInteractedActor();

    AssetManager::DestroyTileMapTexture();
    AssetManager::DestroyMenuIconsTexture();
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
                for (ActorNpc& actor : mNpcs)
                {
                    Vec2 interactPosition = mCharacters[0].GetPosition() + mCharacters[0].mRigidbody.lastVelocity;

                    if (actor.GetPosition() == interactPosition)
                    {
                        mInteractedActor = &actor;
                        if (mInteractedActor)
                            mInteractedActor->mCurrentDialogueMode = ED_GREETING;

                        mInteractMenuIndex = 0;
                        mExplorationState = ES_INTERACTING;

                        return;
                    }
                }

                for (ActorInteractable& interactable : mInteractables)
                {
                    Vec2 interactPosition = mCharacters[0].GetPosition() + mCharacters[0].mRigidbody.lastVelocity;

                    if (interactable.GetPosition() == interactPosition)
                    {
                        mExplorationState = ES_SHOPPING;
                        return;
                    }
                }
            }
            
            if (InputManager::StartPressed())
            {
                mExplorationState = ES_MENUING;
                mPartyMenu.SetCurrentButton(&mPartyMenu.mPartyButton);
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
            else if (InputManager::CancelPressed() && mPartyMenu.GetCurrentButton()->OnCancelAction)
            {
                mPartyMenu.GetCurrentButton()->OnCancelAction();
            }
            break;
        }
    }
}

void SceneExploration::Update(const float dt)
{
    if (mExplorationState == ES_MENUING) return;

    for (Actor& actor : mNpcs)
    {
        actor.UpdateAnimation();
        actor.Update(dt);
    }

    for (CharacterExploration& character : mCharacters)
    {
        character.UpdateMovement(mMapWidth, mMapHeight, mTiles, mCharacters, mNpcs, dt);
        character.Update(dt);

        if (character.mMovement.stepTaken && character.mPartyIndex == 0)
        {
            GameManager::ClearPositionsAndDirections();
            for (CharacterExploration& character : mCharacters)
            {
                GameManager::SetPreviousOverworldPosition(character.GetPosition());
                GameManager::SetPreviousOverworldDirection(character.mRigidbody.lastVelocity);
            }

            for (const SceneEntrance& entrance : mSceneEntrances)
            {
                if (entrance.position == character.GetPosition())
                {
                    GameManager::SetSceneToLoad(entrance.sceneName, entrance.nextSceneEntrance);
                    return;
                }
            }

            if (GameManager::GetIsOverworld())
            {
                mStepsUntilEncounter--;
            }
            if (mStepsUntilEncounter <= 0)
            {
                int terrainIndex = static_cast<int>(character.GetPosition().x) / 16 + (static_cast<int>(character.GetPosition().y) / 16) * mMapWidth;

                GameManager::SetSceneToLoad("Battle", -1, true, mTiles[terrainIndex].terrainType, mEnemyEncounters);
            }
        }
    }
}

void SceneExploration::Render(static SDL_Rect& camera)
{
    if (mDrawMapCentered)
    {
        camera.x = 0 - GraphicsManager::WindowWidth() * 0.5f + mMapWidth * 0.5 * TILE_SIZE * TILE_SPRITE_SCALE;
        camera.y = 0 - GraphicsManager::WindowHeight() * 0.5f + mMapHeight * 0.5f * TILE_SIZE * TILE_SPRITE_SCALE;
    }

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

        GraphicsManager::DrawSpriteRect(AssetManager::GetTileMapTexture(), srcRect, destRect);
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
    for (Actor& actor : mNpcs)
    {
        actor.Render();
    }

    /*for (ActorInteractable& interactable : mInteractables)
    {
        interactable.Render();
    }*/

    // Render Party Characters
    for (int i = mCharacters.size() - 1; i >= 0; i--)
    {
        if (i == 0 && !mDrawMapCentered)
        {
            camera.x = mCharacters[i].GetPosition().x * TILE_SPRITE_SCALE - (GraphicsManager::WindowWidth() * 0.5f);
            camera.y = mCharacters[i].GetPosition().y * TILE_SPRITE_SCALE - (GraphicsManager::WindowHeight() * 0.5f);

            camera.x = Clampf(camera.x, 0, mMapWidth * TILE_SIZE * TILE_SPRITE_SCALE - camera.w);
            camera.y = Clampf(camera.y, 0, mMapHeight * TILE_SIZE * TILE_SPRITE_SCALE - camera.h);
        }

        mCharacters[i].Render();
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
            mInteractMenu.Render();
            DrawCursor();
            break;
        }
        case ES_TALKING:
        {
            GraphicsManager::DrawDialogueBox();
            if(mInteractedActor)
                GraphicsManager::DrawDialogue(mInteractedActor->GetCurrentDialogue());
            break;
        }
        case ES_ASKING:
        {
            break;
        }
        case ES_MENUING:
        { 
            mPartyMenu.Render();
            DrawCursor();
            break;
        }
    }
}

void SceneExploration::DrawCursor()
{
    SDL_Rect& cursorSpriteRect = mBattleIconsMap.at("Cursor").srcRect;

    SDL_Rect destRect;

    switch (mExplorationState)
    {
        case ES_INTERACTING:
        {
            destRect =
            {
                static_cast<int>(mInteractMenu.GetCurrentButton()->mPosition.x - cursorSpriteRect.w * BATTLE_CURSOR_SCALE - 5),
                static_cast<int>(mInteractMenu.GetCurrentButton()->mPosition.y),
                cursorSpriteRect.w * BATTLE_CURSOR_SCALE,
                cursorSpriteRect.h * BATTLE_CURSOR_SCALE
            };
            break;
        }
        case ES_TALKING:
        {
            break;
        }
        case ES_ASKING:
        {
            break;
        }
        case ES_MENUING:
        {
            destRect =
            {
                static_cast<int>(mPartyMenu.GetCurrentButton()->mPosition.x - cursorSpriteRect.w * BATTLE_CURSOR_SCALE - 5),
                static_cast<int>(mPartyMenu.GetCurrentButton()->mPosition.y),
                cursorSpriteRect.w * BATTLE_CURSOR_SCALE,
                cursorSpriteRect.h * BATTLE_CURSOR_SCALE
            };
            break;
        }
    }

    GraphicsManager::DrawSpriteRect(AssetManager::GetMenuIconsTexture(), cursorSpriteRect, destRect);
}