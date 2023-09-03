#include "SceneBattle.h"

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
	// load background image
	SDL_Surface* surface = IMG_Load(mBackgroundImageFilePath.c_str());
	if (surface)
	{
		mBackgroundTexture = SDL_CreateTextureFromSurface(renderer, surface);
	}

	// load enemy sprite sheet
	std::string filePath = "./assets/Enemies.png";
	surface = IMG_Load(filePath.c_str());
	if (surface)
	{
		mEnemiesTexture = SDL_CreateTextureFromSurface(renderer, surface);
	}
	SDL_FreeSurface(surface);

	// load enemy sprites
	std::ifstream file("./assets/Enemies.txt");
	std::string type;
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

	// load enemy attributes and set screen positions
	for (int i = 0; i < encounter.enemyNames.size(); i++)
	{
		Enemy newEnemy = mEnemyMap.at(encounter.enemyNames[i]);
		newEnemy.battleSpawnPosition = encounter.enemyPositions[i];
		newEnemy.LoadEnemyAttributtes(encounter.enemyNames[i]);
		mEnemies.push_back(newEnemy);
	}

	// setup player party
	for (int i = 0; i < PlayerManager::GetCharacterTextures().size(); i++)
	{
		CharacterBattle newCharacter;
		newCharacter.LoadAnimations(PlayerManager::GetCharacterAttributes()[i].characterName);
		newCharacter.mSprite.positionOffset = Vec2(0.0f, 16.0f);
		mPlayerCharacters.push_back(newCharacter);
	}
}

void SceneBattle::Shutdown()
{
	SDL_DestroyTexture(mBackgroundTexture);
	SDL_DestroyTexture(mEnemiesTexture);
}

void SceneBattle::Input()
{
	if (InputManager::UpPressed())
	{
		mBattleMenuIndex--;
		if (mBattleMenuIndex < 0) mBattleMenuIndex = mBattleMenuIndexOptions - 1;
	}
	if (InputManager::DownPressed())
	{
		mBattleMenuIndex++;
		if (mBattleMenuIndex >= mBattleMenuIndexOptions) mBattleMenuIndex = 0;
	}

	if (InputManager::EPressed())
	{
		if (mBattleMenuIndex == 0)
		{
			
		}
		else if (mBattleMenuIndex == 1)
		{

		}
		else if (mBattleMenuIndex == 2)
		{
			
		}
		else if (mBattleMenuIndex == 3)
		{
			SceneManager::SetSceneToLoad(OVERWORLD, -1, true);
		}
	}
}

void SceneBattle::Update(const float dt)
{
}

void SceneBattle::Render(SDL_Renderer* renderer, SDL_Rect& camera)
{
	GraphicsManager::DrawBattleBackground(mBackgroundTexture);

	for (int i = 0; i < mPlayerCharacters.size(); i++)
	{
		Animation& anim = mPlayerCharacters[i].mAnimations[mPlayerCharacters[i].mCurrentAnimation];

		mPlayerCharacters[i].mSprite.srcRect.x = anim.frames[anim.currentFrame].position.x;
		mPlayerCharacters[i].mSprite.srcRect.y = anim.frames[anim.currentFrame].position.y;
		mPlayerCharacters[i].mSprite.srcRect.w = anim.frames[anim.currentFrame].width;
		mPlayerCharacters[i].mSprite.srcRect.h = anim.frames[anim.currentFrame].height;

		SDL_Rect destRect =
		{
			mPlayerCharacterPositions[i].x + mPlayerCharacters[i].mSprite.positionOffset.x * TILE_SPRITE_SCALE,
			mPlayerCharacterPositions[i].y + mPlayerCharacters[i].mSprite.positionOffset.x * TILE_SPRITE_SCALE,
			32 * TILE_SPRITE_SCALE,
			32 * TILE_SPRITE_SCALE
		};

		GraphicsManager::DrawSpriteRect(PlayerManager::GetCharacterTextures()[i], mPlayerCharacters[i].mSprite.srcRect, destRect);
	}

	for (int i = 0; i < mEnemies.size(); i++)
	{
		SDL_Rect destRect =
		{
			mSmallEnemyPositions[mEnemies[i].battleSpawnPosition].x,
			mSmallEnemyPositions[mEnemies[i].battleSpawnPosition].y,
			mEnemies[i].rect.w * TILE_SPRITE_SCALE,
			mEnemies[i].rect.h * TILE_SPRITE_SCALE
		};

		GraphicsManager::DrawSpriteRect(mEnemiesTexture, mEnemies[i].rect, destRect);
	}

	SDL_Rect rect = GraphicsManager::DrawUIBox(
		GraphicsManager::WindowWidth() / 2 + 100,
		GraphicsManager::WindowHeight() - BATTLE_MENU_HEIGHT - DIALOGUE_BOX_BORDER_SIZE * 2,
		BATTLE_MENU_WIDTH,
		BATTLE_MENU_HEIGHT);
	GraphicsManager::DrawString(rect.x + TEXT_PADDING, rect.y + TEXT_PADDING, "Fight", 0xFFFFFFFF);
	GraphicsManager::DrawString(rect.x + TEXT_PADDING, rect.y + TEXT_PADDING + 30, "Magic", 0xFFFFFFFF);
	GraphicsManager::DrawString(rect.x + TEXT_PADDING, rect.y + TEXT_PADDING + 60, "Item", 0xFFFFFFFF);
	GraphicsManager::DrawString(rect.x + TEXT_PADDING, rect.y + TEXT_PADDING + 90, "Run", 0xFFFFFFFF);
	GraphicsManager::DrawUISelector(rect.x, rect.y + 30 * mBattleMenuIndex, rect.w, 30);


	rect = GraphicsManager::DrawUIBox(
		GraphicsManager::WindowWidth() / 2 + BATTLE_MENU_WIDTH + UI_BOX_BORDER_SIZE + 100,
		GraphicsManager::WindowHeight() - BATTLE_PARTY_UI_HEIGHT - DIALOGUE_BOX_BORDER_SIZE * 2,
		BATTLE_PARTY_UI_WIDTH,
		BATTLE_PARTY_UI_HEIGHT);

	for (int i = 0; i < PlayerManager::GetCharacterAttributes().size(); i++)
	{
		const CharacterAttributes& attributes = PlayerManager::GetCharacterAttributes()[i];
		GraphicsManager::DrawString(rect.x + TEXT_PADDING, rect.y + TEXT_PADDING, attributes.characterName.c_str(), 0xFFFFFFFF);

		std::string hpString = std::to_string(attributes.health) + '-' + std::to_string(attributes.healthMax) + "HP";
		std::string mpString = std::to_string(attributes.magic) + '-' + std::to_string(attributes.magicMax) + "MP";

		int hpLength = hpString.length() * Font::fontWidth * TEXT_SIZE + Font::fontSpacing * hpString.length() * TEXT_SIZE;
		int mpLength = mpString.length() * Font::fontWidth * TEXT_SIZE + Font::fontSpacing * mpString.length() * TEXT_SIZE;

		GraphicsManager::DrawString(
			(rect.x + rect.w) - hpLength - BATTLE_PARTY_UI_BUFFER * TEXT_SIZE - mpLength,
			rect.y + TEXT_PADDING,
			hpString.c_str(),
			0xFFFFFFFF);

		GraphicsManager::DrawString(
			(rect.x + rect.w) - mpLength,
			rect.y + TEXT_PADDING,
			mpString.c_str(),
			0xFFFFFFFF);
	}
}