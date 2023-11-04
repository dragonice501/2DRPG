#pragma once

#include <string>
#include <SDL.h>
#include <SDL_audio.h>

class AudioManager
{
public:
	static inline bool Init() { return SDL_Init(SDL_INIT_AUDIO); }

	static void CloseAudioDevice()
	{
		SDL_CloseAudioDevice(deviceID);
		SDL_FreeWAV(wavBuffer);
	}

	static void LoadSound(const char* filePath)
	{
		SDL_LoadWAV(filePath, &wavSpec, &wavBuffer, &wavLength);
		deviceID = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
	}

	static void PlaySound()
	{
		SDL_QueueAudio(deviceID, wavBuffer, wavLength);
		SDL_PauseAudioDevice(deviceID, 0);
	}

	static SDL_AudioSpec wavSpec;
	static Uint32 wavLength;
	static Uint8* wavBuffer;
	static SDL_AudioDeviceID deviceID;
};