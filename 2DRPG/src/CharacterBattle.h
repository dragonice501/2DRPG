#pragma once

#include "GameObject.h"
#include "ActorBattle.h"

#include "Components.h"

#include <SDL.h>
#include <string>
#include <fstream>

class CharacterBattle : public GameObject, public ActorBattle
{
public:
	CharacterBattle() {}
	~CharacterBattle() {}

	void LoadAnimations(std::string name);

	void Input() override;
	void Update(float dt) override;
	void Render() override;


	std::string mAssetID;
	SDL_Texture* mTexture;

	std::map<std::string, Animation> mAnimations;
	std::string mCurrentAnimation = "IdleLeft";
	SpriteComponent mSprite;
};