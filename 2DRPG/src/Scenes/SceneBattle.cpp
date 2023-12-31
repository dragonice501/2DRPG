#include "SceneBattle.h"

#include <algorithm>
#include <random>

SceneBattle::SceneBattle(ETerrainType terrain, const std::vector<EnemyEncounter> enemyEncounters)
{
	switch (terrain)
	{
		case BRIDGE:
		{
			mBackgroundImageName = "BattlePlain";
			break;
		}
		case FOREST:
		{
			mBackgroundImageName = "BattleForest";
			break;
		}
		case PLAIN:
		{
			mBackgroundImageName = "BattlePlain";
			break;
		}
		case RIVER:
		{
			mBackgroundImageName = "BattleRiver";
			break;
		}
		case ROAD:
		{
			mBackgroundImageName = "BattlePlain";
			break;
		}
		case THICKET:
		{
			mBackgroundImageName = "BattleThicket";
			break;
		}
	}

	mEnemyEncounters = enemyEncounters;

	mBattleMenu.mFightButton.OnUpAction = [this]()
	{
		mBattleMenu.SetCurrentButton(&mBattleMenu.mRunButton);
	};
	mBattleMenu.mFightButton.OnDownAction = [this]()
	{
		mBattleMenu.SetCurrentButton(&mBattleMenu.mMagicButton);
	};
	mBattleMenu.mFightButton.OnAcceptAction = [this]()
	{
		SelectFirstEnemy();
		mBattleMenu.SetPreviousButton(&mBattleMenu.mFightButton);
	};

	mBattleMenu.mMagicButton.OnUpAction = [this]()
	{
		mBattleMenu.SetCurrentButton(&mBattleMenu.mFightButton);
	};
	mBattleMenu.mMagicButton.OnDownAction = [this]()
	{
		mBattleMenu.SetCurrentButton(&mBattleMenu.mItemButton);
	};
	mBattleMenu.mMagicButton.OnAcceptAction = [this]()
	{

	};

	mBattleMenu.mItemButton.OnUpAction = [this]()
	{
		mBattleMenu.SetCurrentButton(&mBattleMenu.mMagicButton);
	};
	mBattleMenu.mItemButton.OnDownAction = [this]()
	{
		mBattleMenu.SetCurrentButton(&mBattleMenu.mRunButton);
	};
	mBattleMenu.mItemButton.OnAcceptAction = [this]()
	{

	};

	mBattleMenu.mRunButton.OnUpAction = [this]()
	{
		mBattleMenu.SetCurrentButton(&mBattleMenu.mItemButton);
	};
	mBattleMenu.mRunButton.OnDownAction = [this]()
	{
		mBattleMenu.SetCurrentButton(&mBattleMenu.mFightButton);
	};
	mBattleMenu.mRunButton.OnAcceptAction = [this]()
	{
		GameManager::SetSceneToLoad("Overworld", -2, true);
	};

	mBattleMenu.mSmallEnemyButtons[0].OnDownAction = [this]()
	{
		SearchForEnemyDown(0);
	};
	mBattleMenu.mSmallEnemyButtons[0].OnRightAction = [this]()
	{
		if (SearchForEnemyRight(0)) {}
		else SearchForEnemyDown(0);
	};
	mBattleMenu.mSmallEnemyButtons[0].OnAcceptAction = [this]()
	{
		AcceptEnemyTarget(0);
	};
	mBattleMenu.mSmallEnemyButtons[0].OnCancelAction = [this]()
	{
		mBattleMenu.SetCurrentButton(mBattleMenu.GetPreviousButton());
	};

	mBattleMenu.mSmallEnemyButtons[1].OnUpAction = [this]()
	{
		SearchForEnemyUp(1);
	};
	mBattleMenu.mSmallEnemyButtons[1].OnDownAction = [this]()
	{
		SearchForEnemyDown(1);
	};
	mBattleMenu.mSmallEnemyButtons[1].OnRightAction = [this]()
	{
		if (SearchForEnemyRight(1)) {}
		else SearchForEnemyDown(1);
	};
	mBattleMenu.mSmallEnemyButtons[1].OnAcceptAction = [this]()
	{
		AcceptEnemyTarget(1);
	};
	mBattleMenu.mSmallEnemyButtons[1].OnCancelAction = [this]()
	{
		mBattleMenu.SetCurrentButton(mBattleMenu.GetPreviousButton());
	};

	mBattleMenu.mSmallEnemyButtons[2].OnUpAction = [this]()
	{
		SearchForEnemyUp(2);
	};
	mBattleMenu.mSmallEnemyButtons[2].OnRightAction = [this]()
	{
		if (SearchForEnemyRight(2)) {}
		else SearchForEnemyDown(2);
	};
	mBattleMenu.mSmallEnemyButtons[2].OnAcceptAction = [this]()
	{
		AcceptEnemyTarget(2);
	};
	mBattleMenu.mSmallEnemyButtons[2].OnCancelAction = [this]()
	{
		mBattleMenu.SetCurrentButton(mBattleMenu.GetPreviousButton());
	};

	mBattleMenu.mSmallEnemyButtons[3].OnDownAction = [this]()
	{
		SearchForEnemyDown(3);
	};
	mBattleMenu.mSmallEnemyButtons[3].OnLeftAction = [this]()
	{
		if (SearchForEnemyLeft(3)) return;
		else SearchForEnemyUp(3);
	};
	mBattleMenu.mSmallEnemyButtons[3].OnAcceptAction = [this]()
	{
		AcceptEnemyTarget(3);
	};
	mBattleMenu.mSmallEnemyButtons[3].OnCancelAction = [this]()
	{
		mBattleMenu.SetCurrentButton(mBattleMenu.GetPreviousButton());
	};

	mBattleMenu.mSmallEnemyButtons[4].OnUpAction = [this]()
	{
		SearchForEnemyUp(4);
	};
	mBattleMenu.mSmallEnemyButtons[4].OnDownAction = [this]()
	{
		SearchForEnemyDown(4);
	};
	mBattleMenu.mSmallEnemyButtons[4].OnLeftAction = [this]()
	{
		if (SearchForEnemyLeft(4)) return;
		else SearchForEnemyUp(4);
	};
	mBattleMenu.mSmallEnemyButtons[4].OnAcceptAction = [this]()
	{
		AcceptEnemyTarget(4);
	};
	mBattleMenu.mSmallEnemyButtons[4].OnCancelAction = [this]()
	{
		mBattleMenu.SetCurrentButton(mBattleMenu.GetPreviousButton());
	};

	mBattleMenu.mSmallEnemyButtons[5].OnUpAction = [this]()
	{
		SearchForEnemyUp(5);
	};
	mBattleMenu.mSmallEnemyButtons[5].OnLeftAction = [this]()
	{
		if (SearchForEnemyLeft(5)) return;
		else SearchForEnemyUp(5);
	};
	mBattleMenu.mSmallEnemyButtons[5].OnAcceptAction = [this]()
	{
		AcceptEnemyTarget(5);
	};
	mBattleMenu.mSmallEnemyButtons[5].OnCancelAction = [this]()
	{
		mBattleMenu.SetCurrentButton(mBattleMenu.GetPreviousButton());
	};

	for (int i = 0; i < mBattleMenu.mSmallEnemyButtons.size(); i++)
		mBattleMenu.mSmallEnemyButtons[i].mPosition = mSmallEnemyPositions[i] + Vec2(0.0f, 32 * TILE_SPRITE_SCALE);

	mBattleMenu.SetCurrentButton(&mBattleMenu.mFightButton);
}

void SceneBattle::Setup(SDL_Renderer* renderer)
{
	// Load background image
	AssetManager::CreateBattleBackgroundTexture(mBackgroundImageName);
	AssetManager::CreateEnemiesTexture("Enemies");
	AssetManager::CreateMenuIconsTexture();

	// Load icons map
	std::string basePath = SDL_GetBasePath();
	std::string filePath = "assets\\files\\BattleIcons.txt";
	std::ifstream battleIconsFile(basePath + filePath);
	std::string type;
	while (battleIconsFile >> type)
	{
		if (type == "Cursor")
		{
			SpriteComponent newSprite;

			battleIconsFile >> newSprite.srcRect.x >> newSprite.srcRect.y >> newSprite.srcRect.w >> newSprite.srcRect.h;
			mBattleIconsMap.emplace("Cursor", newSprite);
		}
	}

	// Load enemy sprites
	filePath = "assets\\files\\EnemySprites.txt";
	std::ifstream file(basePath + filePath);
	while (file >> type)
	{
		if (type == "Enemy")
		{
			std::string name;
			int xOffset, yOffset, width, height;

			file >> name >> xOffset >> yOffset >> width >> height;

			Enemy newEnemy = { xOffset, yOffset, width, height };
			mEnemyMap.emplace(name, newEnemy);
		}
	}

	// Pick and create a random encounter
	EnemyEncounter encounter;
	int randomIndex = rand() % mEnemyEncounters.size();
	for (int i = 0; i < mEnemyEncounters.size(); i++)
	{
		if (i == randomIndex)
		{
			encounter = mEnemyEncounters[i];
			break;
		}
	}

	// Load enemy attributes and set screen positions
	for (int i = 0; i < encounter.enemyNames.size(); i++)
	{
		Enemy newEnemy = mEnemyMap.at(encounter.enemyNames[i]);
		newEnemy.position = mSmallEnemyPositions[encounter.enemyPositions[i]];
		newEnemy.LoadEnemyAttributtes(encounter.enemyNames[i]);
		mEnemies.push_back(newEnemy);

		EnemyBattle* newBattleEnemy = new EnemyBattle();
		newBattleEnemy->rect = mEnemyMap.at(encounter.enemyNames[i]).rect;
		newBattleEnemy->battlePosition = mSmallEnemyPositions[encounter.enemyPositions[i]];
		newBattleEnemy->mEnemyPositionIndex = encounter.enemyPositions[i];
		newBattleEnemy->isEnemy = true;
		newBattleEnemy->LoadEnemyAttributtes(encounter.enemyNames[i]);

		mBattleEnemies.push_back(newBattleEnemy);
	}

	// Setup player party
	for (int i = 0; i < PlayerManager::GetCharacterAttributes().size(); i++)
	{
		CharacterBattle newCharacter;
		std::string name;
		switch (PlayerManager::GetCharacterAttributes()[i].characterClass)
		{
			case DANCER:
			{
				name = "Dancer";
				break;
			}
			case KNIGHT:
			{
				name = "Knight";
				break;
			}
			case MAGE:
			{
				name = "Mage";
				break;
			}
			case PALADIN:
			{
				name = "Paladin";
				break;
			}
		}


		AssetManager::CreateAsset(name, name);

		newCharacter.LoadAnimations(name);
		newCharacter.mSprite.positionOffset = Vec2(0.0f, 16.0f);

		mPlayerCharacters.push_back(newCharacter);

		CharacterBattle* newBattleCharacter = new CharacterBattle();
		newBattleCharacter->LoadAnimations(name);
		newBattleCharacter->mAssetID = name;
		newBattleCharacter->battlePosition = mPlayerCharacterPositions[i];
		newBattleCharacter->mSprite.positionOffset = Vec2(0.0f, 16.0f);
		newBattleCharacter->attributes = PlayerManager::GetCharacterAttributes()[i];

		mBattleCharacters.push_back(newBattleCharacter);
	}

	BuildTurnOrder();
	mBattleState = BS_MONSTERS_APPEARED;

	AudioManager::GetMusic("Decisive Battle.wav");
	AudioManager::FadeInMusic("Decisive Battle.wav", 1000);
}

void SceneBattle::Shutdown()
{
	for (CharacterBattle* character : mBattleCharacters)
	{
		delete character;
	}

	for (EnemyBattle* enemy : mBattleEnemies)
	{
		delete enemy;
	}

	AssetManager::DestroyBattleBackgroundTexture();
	AssetManager::DestroyEnemiesTexture();
	AssetManager::DestroyMenuIconsTexture();
	AssetManager::DestroyAssetMap();

	AudioManager::FadeOutMusic(500);
}

void SceneBattle::Input()
{
	switch (mBattleState)
	{
		case BS_SELECTING_ACTION:
		{
			if (InputManager::UpPressed() && mBattleMenu.GetCurrentButton()->OnUpAction)
			{
				mBattleMenu.GetCurrentButton()->OnUpAction();
				AudioManager::PlaySFX("blip.wav");
			}
			else if (InputManager::DownPressed() && mBattleMenu.GetCurrentButton()->OnDownAction)
			{
				mBattleMenu.GetCurrentButton()->OnDownAction();
				AudioManager::PlaySFX("blip.wav");
			}
			else if (InputManager::RightPressed() && mBattleMenu.GetCurrentButton()->OnRightAction)
			{
				mBattleMenu.GetCurrentButton()->OnRightAction();
				AudioManager::PlaySFX("blip.wav");
			}
			else if (InputManager::LeftPressed() && mBattleMenu.GetCurrentButton()->OnLeftAction)
			{
				mBattleMenu.GetCurrentButton()->OnLeftAction();
				AudioManager::PlaySFX("blip.wav");
			}
			else if (InputManager::AcceptPressed() && mBattleMenu.GetCurrentButton()->OnAcceptAction)
			{
				mBattleMenu.GetCurrentButton()->OnAcceptAction();
				AudioManager::PlaySFX("blip.wav");
			}
			else if (InputManager::CancelPressed() && mBattleMenu.GetCurrentButton()->OnCancelAction)
			{
				mBattleMenu.GetCurrentButton()->OnCancelAction();
				AudioManager::PlaySFX("blip.wav");
			}
			break;
		}
		case BS_SELECTING_TARGET:
		{
			mBattleSelectedEnemyIndex--;

			if (mBattleSelectedEnemyIndex < 0) mBattleSelectedEnemyIndex = mBattleEnemies.size() - 1;

			break;
		}
		case BS_SELECTING_ITEM:
		{
			break;
		}
	}
}

void SceneBattle::Update(const float dt)
{
	switch (mBattleState)
	{
		case BS_MONSTERS_APPEARED:
		{
			mBattleEventTimeRemaining -= dt;
			if (mBattleEventTimeRemaining <= 0)
			{
				mBattleEventTimeRemaining = mBattleEventTime;
				if (!mBattleTurns[mTurnIndex]->isEnemy)
				{
					mBattleState = BS_SELECTING_ACTION;
					SetPlayerIndex();
				}
				else
				{
					mBattleState = BS_ENEMY_ATTACKING;
				}
			}
			break;
		}
		case BS_SELECTING_ACTION:
			break;
		case BS_SELECTING_TARGET:
			break;
		case BS_SELECTING_ITEM:
			break;
		case BS_PLAYER_ATTACKING:
		{
			mTurnTimeRemaining -= dt;
			if (mTurnTimeRemaining <= 0)
			{
				mTurnTimeRemaining = mTurnTime;
				mBattleState = BS_PLAYER_ATTACK_RESULT;

				mDamageDealt =
					mBattleTurns[mTurnIndex]->attributes.strength + PlayerManager::GetPlayerWeaponDamage(mSelectedCharacterIndex) -
					mBattleEnemies[mBattleSelectedEnemyIndex]->attributes.defense;
				if (mDamageDealt <= 0) mDamageDealt = 1;
			}
			break;
		}
		case BS_PLAYER_ATTACK_RESULT:
		{
			mTurnTimeRemaining -= dt;
			if (mTurnTimeRemaining <= 0)
			{
				mTurnTimeRemaining = mTurnTime;

				mBattleEnemies[mBattleSelectedEnemyIndex]->attributes.health -= mDamageDealt;
				CharacterAttributes& enemyAttributes = mBattleEnemies[mBattleSelectedEnemyIndex]->attributes;

				if (enemyAttributes.health <= 0)
				{
					enemyAttributes.health = 0;
					mBattleState = BS_ENEMY_DIED;
				}
				else
				{
					NextTurn();
				}
			}

			break;
		}
		case BS_PLAYER_DIED:
		{
			mTurnTimeRemaining -= dt;
			if (mTurnTimeRemaining <= 0)
			{
				mTurnTimeRemaining = mTurnTime;

				NextTurn();
			}
			break;
		}
		case BS_ENEMY_ATTACKING:
		{
			mTurnTimeRemaining -= dt;
			if (mTurnTimeRemaining <= 0)
			{
				mTurnTimeRemaining = mTurnTime;
				mBattleState = BS_ENEMY_ATTACK_RESULT;

				mDamageDealt =
					mBattleTurns[mTurnIndex]->attributes.strength -
					mBattleCharacters[mEnemyTargetIndex]->attributes.defense;
				if (mDamageDealt <= 0) mDamageDealt = 1;
			}
			break;
		}
		case BS_ENEMY_ATTACK_RESULT:
		{
			mTurnTimeRemaining -= dt;
			if (mTurnTimeRemaining <= 0)
			{
				mTurnTimeRemaining = mTurnTime;

				mBattleCharacters[mEnemyTargetIndex]->attributes.health -= mDamageDealt;

				NextTurn();
			}
			break;
		}
		case BS_ENEMY_DIED:
		{
			mTurnTimeRemaining -= dt;
			if (mTurnTimeRemaining <= 0)
			{
				mTurnTimeRemaining = mTurnTime;
				mBattleExpPool += mBattleEnemies[mBattleSelectedEnemyIndex]->attributes.exp;
				mBattleGoldPool += mBattleEnemies[mBattleSelectedEnemyIndex]->mEnemyGold;

				for (int i = 0; i < mBattleTurns.size(); i++)
				{
					if (mBattleTurns[i] == mBattleEnemies[mBattleSelectedEnemyIndex])
					{
						mBattleTurns.erase(mBattleTurns.begin() + i);

						if (i < mTurnIndex) mTurnIndex--;

						break;
					}
				}

				delete mBattleEnemies[mBattleSelectedEnemyIndex];
				mBattleEnemies.erase(mBattleEnemies.begin() + mBattleSelectedEnemyIndex);

				if (mBattleEnemies.size() == 0) mBattleState = BS_MONSTERS_DEFEATED;
				else NextTurn();
			}
			break;
		}
		case BS_MONSTERS_DEFEATED:
		{
			mBattleEventTimeRemaining -= dt;
			if (mBattleEventTimeRemaining <= 0)
			{
				mBattleEventTimeRemaining = mBattleEventTime;
				
				mBattleState = BS_GOLD_GAINED;
			}
			break;
		}
		case BS_PARTY_DEFEATED:
		{
			break;
		}
		case BS_GOLD_GAINED:
		{
			mBattleEventTimeRemaining -= dt;
			if (mBattleEventTimeRemaining <= 0)
			{
				mBattleEventTimeRemaining = mBattleEventTime;

				PlayerManager::AddGold(mBattleGoldPool);
				mBattleState = BS_EXP_GAINED;
			};
			break;
		}
		case BS_EXP_GAINED:
		{
			mBattleEventTimeRemaining -= dt;
			if (mBattleEventTimeRemaining <= 0)
			{
				mBattleEventTimeRemaining = mBattleEventTime;

				// Set Party attributes with battle attributes
				for (int i = 0; i < mBattleCharacters.size(); i++)
				{
					CharacterAttributes& characterAttributes = PlayerManager::GetCharacterAttributes()[i];
					characterAttributes = mBattleCharacters[i]->attributes;
					characterAttributes.exp += mBattleExpPool;
				}

				if (PlayerManager::CheckLevelUp(mLevelUpIndex))
				{
					mBattleState = BS_LEVEL_UP;
				}
				else
				{
					mBattleState = BS_BATTLE_END;
				}
			}
			break;
		}
		case BS_LEVEL_UP:
		{
			mBattleEventTimeRemaining -= dt;
			if (mBattleEventTimeRemaining <= 0)
			{
				mBattleEventTimeRemaining = mBattleEventTime;

				PlayerManager::LevelUp(mLevelUpIndex, mStatArray);

				// Find First Stat Increase
				mStatIndex = 0;
				while (!mStatArray[mStatIndex])
				{
					mStatIndex++;
				}

				mBattleState = BS_STAT_INCREASE;
			}
			break;
		}
		case BS_STAT_INCREASE:
		{
			mBattleEventTimeRemaining -= dt;
			if (mBattleEventTimeRemaining <= 0)
			{
				mBattleEventTimeRemaining = mBattleEventTime;

				mStatIndex++;
				while (!mStatArray[mStatIndex])
				{
					mStatIndex++;
				}
				if (mStatIndex >= 8)
				{
					for (int i = 0; i < 8; i++) mStatArray[i] = false;
					mStatIndex = 0;

					mLevelUpIndex++;
					if (!PlayerManager::CheckLevelUp(mLevelUpIndex))
					{
						mBattleState = BS_BATTLE_END;
					}
					else
					{
						mBattleState = BS_LEVEL_UP;
					}
				}
			}
			break;
		}
		case BS_BATTLE_END:
		{
			mTurnTimeRemaining -= dt;
			if (mTurnTimeRemaining <= 0)
			{
				GameManager::SetSceneToLoad("Overworld", -2, true);
			}
			break;
		}
	}
}

void SceneBattle::BuildTurnOrder()
{
	for (CharacterBattle* character : mBattleCharacters)
	{
		if(character->IsAlive())
			mBattleTurns.push_back(character);
	}

	for (EnemyBattle* enemy : mBattleEnemies)
	{
		if(enemy->IsAlive())
			mBattleTurns.push_back(enemy);
	}

	std::sort(mBattleTurns.begin(), mBattleTurns.end(), [](const ActorBattle* lhs, const ActorBattle* rhs)
	{
		return lhs->attributes.speed > rhs->attributes.speed;
	});
}

void SceneBattle::NextTurn()
{
	mTurnIndex++;
	if (mTurnIndex >= mBattleTurns.size())
	{
		mTurnIndex = 0;
		mBattleTurns.clear();
		BuildTurnOrder();

		if (!mBattleTurns[mTurnIndex]->isEnemy)
		{
			mBattleState = BS_SELECTING_ACTION;
			mBattleMenu.SetCurrentButton(&mBattleMenu.mFightButton);
			SetPlayerIndex();
		}
		else
		{
			mBattleState = BS_ENEMY_ATTACKING;
		}
	}

	if (!mBattleTurns[mTurnIndex]->isEnemy)
	{
		mBattleState = BS_SELECTING_ACTION;
		mBattleMenu.SetCurrentButton(&mBattleMenu.mFightButton);
		mBattleSelectedEnemyIndex = 0;
		SetPlayerIndex();
	}
	else
	{
		mBattleState = BS_ENEMY_ATTACKING;
	}

	if(mBattleState == BS_ENEMY_ATTACKING)
	{
		SetEnemyAttackTarget();
	}
}

void SceneBattle::SetPlayerIndex()
{
	mBattleState = BS_SELECTING_ACTION;
	for (int i = 0; i < mBattleCharacters.size(); i++)
	{
		if (mBattleCharacters[i] == mBattleTurns[mTurnIndex])
		{
			mCurrentPlayerIndex = i;
			break;
		}
	}
}

void SceneBattle::SelectFirstEnemy()
{
	if (mBattleEnemies.size() > 0)
	{
		mBattleMenu.SetCurrentButton(&mBattleMenu.mSmallEnemyButtons[mBattleEnemies[0]->mEnemyPositionIndex]);
	}
}

bool SceneBattle::SelectEnemy(int index)
{
	for (int i = 0; i < mBattleEnemies.size(); i++)
	{
		if (mBattleEnemies[i]->mEnemyPositionIndex == index)
		{
			mBattleMenu.SetCurrentButton(&mBattleMenu.mSmallEnemyButtons[mBattleEnemies[i]->mEnemyPositionIndex]);
			return true;
		}
	}

	return false;
}

bool SceneBattle::SearchForEnemyUp(int index)
{
	if (mBattleEnemies.size() == 1) return false;

	int i = index;
	while (true)
	{
		i--;
		if (i < 0) i = 5;

		if (SelectEnemy(i)) break;
	}
}

bool SceneBattle::SearchForEnemyDown(int index)
{
	if (mBattleEnemies.size() == 1) return false;

	int i = index;
	while (true)
	{
		i++;
		if (i > 5) i = 0;

		if (SelectEnemy(i)) break;
	}
}

bool SceneBattle::SearchForEnemyLeft(int index)
{
	if (mBattleEnemies.size() == 1) return false;

	int i = index;
	if (i - 3 >= 0)
	{
		if (SelectEnemy(i - 3)) return true;
	}

	return false;
}

bool SceneBattle::SearchForEnemyRight(int index)
{
	if (mBattleEnemies.size() == 1) return false;

	int i = index;
	if (i + 3 <= 5)
	{
		if (SelectEnemy(i + 3)) return true;
	}

	return false;
}

void SceneBattle::AcceptEnemyTarget(int index)
{
	for (int i = 0; i < mBattleEnemies.size(); i++)
	{
		if (mBattleEnemies[i]->mEnemyPositionIndex == index)
		{
			mBattleSelectedEnemyIndex = i;
			mBattleState = BS_PLAYER_ATTACKING;
		}
	}
}

void SceneBattle::SetEnemyAttackTarget()
{
	mEnemyTargetIndex = rand() % 4;
}

void SceneBattle::Render(SDL_Rect& camera)
{
	GraphicsManager::DrawBattleBackground(AssetManager::GetBattleBackgroundTexture());

	// Draw Party
	for (CharacterBattle* character : mBattleCharacters)
	{
		Animation& anim = character->mAnimations[character->mCurrentAnimation];

		character->mSprite.srcRect.x = anim.frames[anim.currentFrame].position.x;
		character->mSprite.srcRect.y = anim.frames[anim.currentFrame].position.y;
		character->mSprite.srcRect.w = anim.frames[anim.currentFrame].width;
		character->mSprite.srcRect.h = anim.frames[anim.currentFrame].height;

		SDL_Rect destRect =
		{
			character->battlePosition.x + character->mSprite.positionOffset.x * TILE_SPRITE_SCALE,
			character->battlePosition.y + character->mSprite.positionOffset.x * TILE_SPRITE_SCALE,
			48 * TILE_SPRITE_SCALE,
			48 * TILE_SPRITE_SCALE
		};

		GraphicsManager::DrawSpriteRect(AssetManager::GetAsset(character->mAssetID), character->mSprite.srcRect, destRect);
	}

	// Draw Enemies
	for (EnemyBattle* enemy : mBattleEnemies)
	{
		if (enemy->IsAlive())
		{
			SDL_Rect destRect =
			{
				enemy->battlePosition.x,
				enemy->battlePosition.y,
				enemy->rect.w * TILE_SPRITE_SCALE * 1.5f,
				enemy->rect.h * TILE_SPRITE_SCALE * 1.5f
			};

			GraphicsManager::DrawSpriteRect(AssetManager::GetEnemiesTexture(), enemy->rect, destRect);
		}
	}

	// Draw UI
	SDL_Rect rect;
	std::string battleString;
	switch (mBattleState)
	{
		case BS_MONSTERS_APPEARED:
		{
			battleString = "Monsters Appeared";

			DrawBattleEvent(rect, battleString);
			break;
		}
		case BS_SELECTING_ACTION:
		{
			DrawBattleMenu(rect);
			DrawCursor();
			break;
		}
		case BS_SELECTING_TARGET:
		{
			DrawBattleMenu(rect);
			DrawCursor();
			break;
		}
		case BS_SELECTING_ITEM:
		{
			break;
		}
		case BS_PLAYER_ATTACKING:
		{
			battleString =
				mBattleTurns[mTurnIndex]->attributes.characterName +
				" attacks " +
				mBattleEnemies[mBattleSelectedEnemyIndex]->attributes.characterName;

			DrawBattleEvent(rect, battleString);
			break;
		}
		case BS_PLAYER_ATTACK_RESULT:
		{
			battleString =
				mBattleTurns[mTurnIndex]->attributes.characterName +
				" did " +
				std::to_string(mDamageDealt) +
				" damage ";

			DrawBattleEvent(rect, battleString);
			break;
		}
		case BS_PLAYER_DIED:
		{
			/*battleString =
				PlayerManager::GetCharacterAttributes()[mTurnOrder[mTurnIndex].characterIndex].characterName +
				" fainted";

			DrawBattleEvent(renderer, rect, battleString);*/
			break;
		}
		case BS_ENEMY_ATTACKING:
		{
			battleString =
				mBattleTurns[mTurnIndex]->attributes.characterName +
				" attacks " +
				mBattleCharacters[mEnemyTargetIndex]->attributes.characterName;

			DrawBattleEvent(rect, battleString);
			break;
		}
		case BS_ENEMY_ATTACK_RESULT:
		{
			battleString =
				mBattleTurns[mTurnIndex]->attributes.characterName +
				" did " +
				std::to_string(mDamageDealt) +
				" damage ";

			DrawBattleEvent(rect, battleString);
			break;
		}
		case BS_ENEMY_DIED:
		{
			battleString =
				mBattleEnemies[mBattleSelectedEnemyIndex]->attributes.characterName +
				" perished";

			DrawBattleEvent(rect, battleString);
			break;
		}
		case BS_MONSTERS_DEFEATED:
		{
			battleString = "Monsters Perished";

			DrawBattleEvent(rect, battleString);
			break;
		}
		case BS_PARTY_DEFEATED:
		{

			break;
		}
		case BS_GOLD_GAINED:
		{
			battleString =
				std::to_string(mBattleGoldPool) +
				" Gold Gained";

			DrawBattleEvent(rect, battleString);
			break;
		}
		case BS_EXP_GAINED:
		{
			battleString =
				std::to_string(mBattleExpPool) +
				" Exp Gained";

			DrawBattleEvent(rect, battleString);
			break;
		}
		case BS_LEVEL_UP:
		{
			battleString = PlayerManager::GetCharacterAttributes()[mLevelUpIndex].characterName + " Level Up";

			DrawBattleEvent(rect, battleString);
			break;
		}
		case BS_STAT_INCREASE:
		{
			switch (mStatIndex)
			{
				case 0:
				{
					battleString = "Health Up";
					break;
				}
				case 1:
				{
					battleString = "Magic Up";
					break;
				}
				case 2:
				{
					battleString = "Strength Up";
					break;
				}
				case 3:
				{
					battleString = "Defense Up";
					break;
				}
				case 4:
				{
					battleString = "Intelligence Up";
					break;
				}
				case 5:
				{
					battleString = "Speed Up";
					break;
				}
				case 6:
				{
					battleString = "Skill Up";
					break;
				}
				case 7:
				{
					battleString = "Luck Up";
					break;
				}
			}

			DrawBattleEvent(rect, battleString);
			break;
		}
		case BS_BATTLE_END:
		{
			break;
		}
	}
}

void SceneBattle::DrawBattleMenu(SDL_Rect& rect)
{
	for (int i = 4; i < mBattleMenu.mPartyStatsPanel.mText.size(); i++)
	{
		std::string& string = mBattleMenu.mPartyStatsPanel.mText[i]->mText;
		const CharacterAttributes& attributes = mBattleCharacters[i - 4]->attributes;

		string = std::to_string(attributes.health) + '/' + std::to_string(attributes.healthMax) + "HP" + ' ';
		string += std::to_string(attributes.magic) + '/' + std::to_string(attributes.magicMax) + "MP";
	}

	mBattleMenu.Render();
}

void SceneBattle::DrawCursor()
{
	SDL_Rect& cursorSpriteRect = mBattleIconsMap.at("Cursor").srcRect;

	SDL_Rect destRect =
	{
		mBattleMenu.GetCurrentButton()->mPosition.x - cursorSpriteRect.w * BATTLE_CURSOR_SCALE - 5,
		mBattleMenu.GetCurrentButton()->mPosition.y,
		cursorSpriteRect.w * BATTLE_CURSOR_SCALE,
		cursorSpriteRect.h * BATTLE_CURSOR_SCALE
	};

	GraphicsManager::DrawSpriteRect(AssetManager::GetMenuIconsTexture(), cursorSpriteRect, destRect);

	destRect =
	{
		static_cast<int>(mBattleMenu.mPartyStatsPanel.mText[mCurrentPlayerIndex]->mPosition.x - cursorSpriteRect.w * BATTLE_CURSOR_SCALE - 5),
		static_cast<int>(mBattleMenu.mPartyStatsPanel.mText[mCurrentPlayerIndex]->mPosition.y),
		cursorSpriteRect.w * BATTLE_CURSOR_SCALE,
		cursorSpriteRect.h * BATTLE_CURSOR_SCALE
	};

	GraphicsManager::DrawSpriteRect(AssetManager::GetMenuIconsTexture(), cursorSpriteRect, destRect);
}

void SceneBattle::DrawBattleEvent(SDL_Rect& rect, const std::string& eventString)
{
	GraphicsManager::DrawBattleEvent(eventString);
}