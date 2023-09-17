#include "SceneBattle.h"

#include <algorithm>

SceneBattle::SceneBattle(ETerrainType terrain, const std::vector<EnemyEncounter> enemyEncounters)
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
		case RIVER:
		{
			mBackgroundImageFilePath = "./assets/BattleRiver.png";
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

	mEnemyEncounters = enemyEncounters;
}

void SceneBattle::Setup(SDL_Renderer* renderer)
{
	// Load background image
	SDL_Surface* surface = IMG_Load(mBackgroundImageFilePath.c_str());
	if (surface)
	{
		mBackgroundTexture = SDL_CreateTextureFromSurface(renderer, surface);
	}
	SDL_FreeSurface(surface);

	// Load battle icons
	surface = IMG_Load(mBattleIconsFilePath.c_str());
	if (surface)
	{
		mBattleIconsTexture = SDL_CreateTextureFromSurface(renderer, surface);
	}
	SDL_FreeSurface(surface);

	std::ifstream battleIconsFile("./assets/BattleIcons.txt");
	std::string type;
	while (battleIconsFile >> type)
	{
		if (type == "Cursor")
		{
			Sprite newSprite;

			battleIconsFile >> newSprite.srcRect.x >> newSprite.srcRect.y >> newSprite.srcRect.w >> newSprite.srcRect.h;
			mBattleIconsMap.emplace("Cursor", newSprite);
		}
	}

	// Load enemy sprite sheet
	std::string filePath = "./assets/Enemies.png";
	surface = IMG_Load(filePath.c_str());
	if (surface)
	{
		mEnemiesTexture = SDL_CreateTextureFromSurface(renderer, surface);
	}
	SDL_FreeSurface(surface);

	// Load enemy sprites
	std::ifstream file("./assets/EnemySprites.txt");
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

	// Pick random encounter
	EnemyEncounter encounter;
	srand(time(NULL));
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
		newBattleEnemy->isEnemy = true;
		newBattleEnemy->LoadEnemyAttributtes(encounter.enemyNames[i]);

		mBattleEnemies.push_back(newBattleEnemy);
	}

	// Setup player party
	for (int i = 0; i < PlayerManager::GetCharacterTextures().size(); i++)
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
				name = "Sigurd";
				break;
			}
		}

		newCharacter.LoadAnimations(name);
		newCharacter.mSprite.positionOffset = Vec2(0.0f, 16.0f);

		mPlayerCharacters.push_back(newCharacter);

		CharacterBattle* newBattleCharacter = new CharacterBattle();
		newBattleCharacter->LoadAnimations(name);
		newBattleCharacter->mTexture = PlayerManager::GetCharacterTextures()[i];
		newBattleCharacter->battlePosition = mPlayerCharacterPositions[i];
		newBattleCharacter->mSprite.positionOffset = Vec2(0.0f, 16.0f);
		newBattleCharacter->attributes = PlayerManager::GetCharacterAttributes()[i];

		mBattleCharacters.push_back(newBattleCharacter);
	}

	BuildTurnOrder();
	mBattleState = BS_MONSTERS_APPEARED;
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

	SDL_DestroyTexture(mBackgroundTexture);
	SDL_DestroyTexture(mBattleIconsTexture);
	SDL_DestroyTexture(mEnemiesTexture);
}

void SceneBattle::Input()
{
	if (InputManager::UpPressed())
	{
		switch (mBattleState)
		{
			case BS_SELECTING_ACTION:
			{

				mBattleMenuIndex--;
				if (mBattleMenuIndex < 0) mBattleMenuIndex = mBattleMenuIndexOptions - 1;
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
	if (InputManager::DownPressed())
	{
		switch (mBattleState)
		{
			case BS_SELECTING_ACTION:
			{
				mBattleMenuIndex++;
				if (mBattleMenuIndex >= mBattleMenuIndexOptions) mBattleMenuIndex = 0;
				break;
			}
			case BS_SELECTING_TARGET:
			{
				mBattleSelectedEnemyIndex++;

				if (mBattleSelectedEnemyIndex >= mBattleEnemies.size()) mBattleSelectedEnemyIndex = 0;

				break;
			}
			case BS_SELECTING_ITEM:
			{

				break;
			}
		}
	}

	if (InputManager::EPressed())
	{
		switch (mBattleState)
		{
			case BS_SELECTING_ACTION:
			{
				if (mBattleMenuIndex == 0)
				{
					mBattleState = BS_SELECTING_TARGET;
				}
				else if (mBattleMenuIndex == 1)
				{

				}
				else if (mBattleMenuIndex == 2)
				{

				}
				else if (mBattleMenuIndex == 3)
				{
					GameManager::SetSceneToLoad(OVERWORLD, -2, true);
				}
				break;
			}
			case BS_SELECTING_TARGET:
			{
				mBattleState = BS_PLAYER_ATTACKING;
				break;
			}
			case BS_SELECTING_ITEM:
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
			mBattleEndTimeRemaing -= dt;
			if (mBattleEndTimeRemaing <= 0)
			{
				mBattleEndTimeRemaing = mBattleEndTime;
				if (!mBattleTurns[mTurnIndex]->isEnemy)
				{
					mBattleState = BS_SELECTING_ACTION;
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
					mBattleTurns[mTurnIndex]->attributes.strength -
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
				std::cout << enemyAttributes.characterName << ' ' << enemyAttributes.health << '/' << enemyAttributes.healthMax << std::endl << std::endl;

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
			mBattleEndTimeRemaing -= dt;
			if (mBattleEndTimeRemaing <= 0)
			{
				mBattleEndTimeRemaing = mBattleEndTime;

				for (int i = 0; i < mBattleCharacters.size(); i++)
				{
					PlayerManager::GetCharacterAttributes()[i] = mBattleCharacters[i]->attributes;
				}

				SceneManager::SetSceneToLoad(OVERWORLD, -1, true);
			}
			break;
		}
		case BS_PARTY_DEFEATED:
		{
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

	for (ActorBattle* actor : mBattleTurns)
	{
		std::cout << actor->attributes.characterName << ' ' << actor->attributes.speed << std::endl;
	}

	std::cout << std::endl;
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
		}
		else
		{
			mBattleState = BS_ENEMY_ATTACKING;
		}
	}

	if (!mBattleTurns[mTurnIndex]->isEnemy)
	{
		mBattleState = BS_SELECTING_ACTION;
		mBattleSelectedEnemyIndex = 0;
		for (int i = 0; i < mBattleCharacters.size(); i++)
		{
			if (mBattleCharacters[i] == mBattleTurns[mTurnIndex])
			{
				mCurrentPlayerIndex = i;
				break;
			}
		}
	}
	else mBattleState = BS_ENEMY_ATTACKING;
}

void SceneBattle::Render(SDL_Renderer* renderer, SDL_Rect& camera)
{
	GraphicsManager::DrawBattleBackground(mBackgroundTexture);

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
			32 * TILE_SPRITE_SCALE,
			32 * TILE_SPRITE_SCALE
		};

		GraphicsManager::DrawSpriteRect(character->mTexture, character->mSprite.srcRect, destRect);
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
				enemy->rect.w * TILE_SPRITE_SCALE,
				enemy->rect.h * TILE_SPRITE_SCALE
			};

			GraphicsManager::DrawSpriteRect(mEnemiesTexture, enemy->rect, destRect);
		}
	}

	SDL_Rect rect;
	std::string battleString;
	switch (mBattleState)
	{
		case BS_MONSTERS_APPEARED:
		{
			battleString = "Monsters Appeared";

			DrawBattleEvent(renderer, rect, battleString);
			break;
		}
		case BS_SELECTING_ACTION:
		{
			DrawActions(renderer, rect);
			DrawPartyStats(renderer, rect);
			break;
		}
		case BS_SELECTING_TARGET:
		{
			DrawActions(renderer, rect);
			DrawPartyStats(renderer, rect);
			DrawCursor(renderer);
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

			DrawBattleEvent(renderer, rect, battleString);
			break;
		}
		case BS_PLAYER_ATTACK_RESULT:
		{
			battleString =
				mBattleTurns[mTurnIndex]->attributes.characterName +
				" did " +
				std::to_string(mDamageDealt) +
				" damage ";

			DrawBattleEvent(renderer, rect, battleString);
			break;
		}
		case BS_PLAYER_DIED:
		{
			battleString =
				PlayerManager::GetCharacterAttributes()[mTurnOrder[mTurnIndex].characterIndex].characterName +
				" fainted";

			DrawBattleEvent(renderer, rect, battleString);
			break;
		}
		case BS_ENEMY_ATTACKING:
		{
			battleString =
				mBattleTurns[mTurnIndex]->attributes.characterName +
				" attacks " +
				mBattleCharacters[mEnemyTargetIndex]->attributes.characterName;

			DrawBattleEvent(renderer, rect, battleString);
			break;
		}
		case BS_ENEMY_ATTACK_RESULT:
		{
			battleString =
				mBattleTurns[mTurnIndex]->attributes.characterName +
				" did " +
				std::to_string(mDamageDealt) +
				" damage ";

			DrawBattleEvent(renderer, rect, battleString);
			break;
		}
		case BS_ENEMY_DIED:
		{
			battleString =
				mBattleEnemies[mBattleSelectedEnemyIndex]->attributes.characterName +
				" perished";

			DrawBattleEvent(renderer, rect, battleString);
			break;
		}
		case BS_MONSTERS_DEFEATED:
		{
			battleString = "Monsters Perished";

			DrawBattleEvent(renderer, rect, battleString);
			break;
		}
		case BS_PARTY_DEFEATED:
		{

			break;
		}
	}
}

void SceneBattle::DrawActions(SDL_Renderer* renderer, SDL_Rect& rect)
{
	rect = GraphicsManager::DrawUIBox(
		GraphicsManager::WindowWidth() / 2 + 100,
		GraphicsManager::WindowHeight() - BATTLE_MENU_HEIGHT - DIALOGUE_BOX_BORDER_SIZE * 2,
		BATTLE_MENU_WIDTH,
		BATTLE_MENU_HEIGHT);

	GraphicsManager::DrawString(rect.x + TEXT_PADDING, rect.y + TEXT_PADDING, "Fight");
	GraphicsManager::DrawString(rect.x + TEXT_PADDING, rect.y + TEXT_PADDING + 30, "Magic");
	GraphicsManager::DrawString(rect.x + TEXT_PADDING, rect.y + TEXT_PADDING + 60, "Item");
	GraphicsManager::DrawString(rect.x + TEXT_PADDING, rect.y + TEXT_PADDING + 90, "Run");

	GraphicsManager::DrawUISelector(
		rect.x,
		rect.y + TEXT_PADDING - TEXT_PADDING / 2 + 30 * mBattleMenuIndex,
		rect.w,
		Font::fontHeight * TEXT_SIZE + TEXT_PADDING);
}

void SceneBattle::DrawPartyStats(SDL_Renderer* renderer, SDL_Rect& rect)
{
	rect = GraphicsManager::DrawUIBox(
		GraphicsManager::WindowWidth() / 2 + BATTLE_MENU_WIDTH + UI_BOX_BORDER_SIZE + 100,
		GraphicsManager::WindowHeight() - BATTLE_PARTY_UI_HEIGHT - DIALOGUE_BOX_BORDER_SIZE * 2,
		BATTLE_PARTY_UI_WIDTH,
		BATTLE_PARTY_UI_HEIGHT);

	for (int i = 0; i < mBattleCharacters.size(); i++)
	{
		const CharacterAttributes& attributes = mBattleCharacters[i]->attributes;
		GraphicsManager::DrawString(
			rect.x + TEXT_PADDING,
			rect.y + TEXT_PADDING + BATTLE_TEXT_VERTICAL_PADDING * i,
			attributes.characterName.c_str());

		std::string hpString = std::to_string(attributes.health) + '/' + std::to_string(attributes.healthMax) + "HP";
		std::string mpString = std::to_string(attributes.magic) + '/' + std::to_string(attributes.magicMax) + "MP";

		int hpLength = hpString.length() * Font::fontWidth * TEXT_SIZE + Font::fontSpacing * hpString.length() * TEXT_SIZE;
		int mpLength = mpString.length() * Font::fontWidth * TEXT_SIZE + Font::fontSpacing * mpString.length() * TEXT_SIZE;

		GraphicsManager::DrawString(
			(rect.x + rect.w) - hpLength - BATTLE_PARTY_UI_BUFFER * TEXT_SIZE - mpLength,
			rect.y + TEXT_PADDING + BATTLE_TEXT_VERTICAL_PADDING * i,
			hpString.c_str());

		GraphicsManager::DrawString(
			(rect.x + rect.w) - mpLength,
			rect.y + TEXT_PADDING + BATTLE_TEXT_VERTICAL_PADDING * i,
			mpString.c_str());
	}

	GraphicsManager::DrawUISelector(
		rect.x,
		rect.y + TEXT_PADDING - TEXT_PADDING / 2 + 30 * mCurrentPlayerIndex,
		rect.w,
		Font::fontHeight * TEXT_SIZE + TEXT_PADDING);
}

void SceneBattle::DrawCursor(SDL_Renderer* renderer)
{
	SDL_Rect& cursorSpriteRect = mBattleIconsMap.at("Cursor").srcRect;

	SDL_Rect destRect =
	{
		mBattleEnemies[mBattleSelectedEnemyIndex]->battlePosition.x - cursorSpriteRect.w * BATTLE_CURSOR_SCALE,
		mBattleEnemies[mBattleSelectedEnemyIndex]->battlePosition.y + (mBattleEnemies[mBattleSelectedEnemyIndex]->rect.h / 2) * TILE_SPRITE_SCALE,
		cursorSpriteRect.w * BATTLE_CURSOR_SCALE,
		cursorSpriteRect.h * BATTLE_CURSOR_SCALE
	};

	GraphicsManager::DrawSpriteRect(mBattleIconsTexture, cursorSpriteRect, destRect);
}

void SceneBattle::DrawBattleEvent(SDL_Renderer* renderer, SDL_Rect& rect, const std::string& eventString)
{
	int stringLength = eventString.length() * Font::fontWidth * TEXT_SIZE + Font::fontSpacing * eventString.length() * TEXT_SIZE;

	rect = GraphicsManager::DrawUIBox(
		GraphicsManager::WindowWidth() / 2 - stringLength / 2 - TEXT_PADDING,
		GraphicsManager::WindowHeight() - BATTLE_MENU_HEIGHT - DIALOGUE_BOX_BORDER_SIZE * 2,
		stringLength + TEXT_PADDING * 2,
		Font::fontHeight * TEXT_SIZE + TEXT_PADDING * 2);

	GraphicsManager::DrawString(
		rect.x + TEXT_PADDING,
		rect.y + TEXT_PADDING,
		eventString.c_str());
}