#include "AudioManager.h"

SDL_AudioSpec AudioManager::wavSpec;
Uint32 AudioManager::wavLength;
Uint8* AudioManager::wavBuffer;
SDL_AudioDeviceID AudioManager::deviceID;