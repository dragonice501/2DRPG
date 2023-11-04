#include "AudioManager.h"

std::string AudioManager::basePath = "C:/Users/narga/Desktop/Visual Studio Stuff/2DRPG/2DRPG/assets/audio/";

SDL_AudioSpec AudioManager::wavSpec;
Uint32 AudioManager::wavLength;
Uint8* AudioManager::wavBuffer;
SDL_AudioDeviceID AudioManager::deviceID;

std::map<std::string, Mix_Music*> AudioManager::mMusic;
std::map<std::string, Mix_Chunk*> AudioManager::mSFX;