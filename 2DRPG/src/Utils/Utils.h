#pragma once

enum SceneNames
{
	BATTLE,
	OVERWORLD,
	TOWN,
	NONE
};

enum EMovementState
{
	MS_IDLE,
	MS_MOVING
};

enum ECharacterState
{
	CS_MOVING,
	CS_INTERACT_MENU,
	CS_TALKING,
	CS_ASKING,
	CS_LISTENING
};

enum ECharacterClass
{
	DANCER,
	KNIGHT,
	MAGE,
	PALADIN,
	NO_CLASS
};

enum EBattleState
{
	BS_SELECTING_ACTION,
	BS_SELECTING_TARGET,
	BS_SELECTING_ITEM,
	BS_PLAYER_ATTACKING,
	BS_PLAYER_ATTACK_RESULT,
	BS_ENEMY_ATTACKING,
	BS_ENEMY_ATTACK_RESULT
};

enum EElementAffect
{
	IMMUNE,
	ABSORB,
	HALF,
	NORMAL,
	WEAK
};

enum EDialogueState
{
	DS_PRINTING,
	DS_FINISHED
};

enum ETownTileType
{
	WALKABLE,
	UNWALKABLE
};

// Town Tile Indeces
static size_t mWalkableIndeces[43] =
{
	0,5,6,7,11,12,13,68,69,71,74,100,101,103,130,131,132,133,134,135,142,148,161,
	162,163,164,165,166,167,168,174,180,197,206,238,389,391,394,421,423,424,425,428
};

enum ETerrainType
{
	BRAGI_TOWER,
	BRIDGE,
	CASTLE_DEFENSE,
	CASTLE_WALL,
	CHURCH,
	CLIFF,
	DESERT,
	FOREST,
	MOUNTAIN,
	PEAK,
	PLAIN,
	RIVER,
	ROAD,
	RUINS,
	SAND,
	SEA,
	THICKET,
	VILLAGE,
	UNDEFINED
};

static size_t mBragiTowerIndeces[3] =
{
	625,657,689
};

static size_t mBridgeIndeces[5] =
{
	528,529,530,560,592
};

static size_t mCastleDefenseIndeces[4] =
{
	531,532,624,656
};

static size_t mCastleWallIndeces[35] =
{
	534,535,537,538,565,566,567,568,569,570,597,598,599,600,601,602,661,
	662,664,665,666,692,693,694,695,696,697,698,756,757,758,759,760,761,762
};

static size_t mChurchIndeces[1] =
{
	593
};

static size_t mCliffIndeces[38] =
{
	234,235,236,266,267,268,269,298,299,300,301,320,321,322,323,324,325,326
	,327,328,329,330,331,354,355,360,361,512,513,514,515,516,517,519,544,548,549,551
};

/*size_t mDesertIndeces[] =
{

};*/

static size_t mForestIndeces[16] =
{
	192,193,194,195,196,197,198,199,200,201,224,225,226,227,228,231
};

static size_t mMountainIndeces[59] =
{
	16,17,18,19,23,24,48,49,51,54,55,56,57,58,80,81,82,83,85,86,87,88,113,114,115,117,118,119,120,121,122,123,145,146,150,151,152,153,154,155,
	181,182,183,184,185,186,187,213,214,215,216,217,218,245,246,247,249,279,280
};

/*size_t mPeakIndeces[] =
{

};*/

static size_t mPlainIndeces[45] =
{
	0,1,2,3,4,6,7,8,9,11,12,28,29,30,31,32,33,33,34,35,36,37,38,39,40,41,62,91,
	112,140,201,202,204,205,229,230,232,233,308,309,338,366,495,496,561
};

static size_t mRiverIndeces[17] =
{
	384,385,387,389,390,391,392,393,416,417,419,420,421,422,423,424,425
};

static size_t mRoadIndeces[48] =
{
	64,65,66,67,68,69,70,72,74,75,76,77,96,97,98,99,100,101,103,104,105,107,108,109,128,129,130,
	131,132,133,134,135,136,137,138,139,140,141,160,161,162,163,164,165,166,167,169, 172
};

static size_t mSandIndeces[17] =
{
	448,449,453,454,455,456,457,480,481,485,486,487,488,489,490,491,492
};

static size_t mSeaIndeces[12] =
{
	450,451,452,458,459,460,482,483,484,523,545,546
};

static size_t mThicketIndeces[18] =
{
	256,257,258,259,260,261,262,263,264,265,288,289,290,291,292,295,296,297
};

static size_t mVillageIndeces[3] =
{
	594,595,596
};

float Clampf(const float v, const float min, const float max);

ETownTileType GetTownTileType(const int mapSpriteIndex);
ETerrainType GetTerrainType(const int mapSpriteIndex);
void PrintTerrainType(const ETerrainType terrain);

#include <string>

void ConvertDialogueDashes(std::string& string);