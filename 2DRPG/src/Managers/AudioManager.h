#pragma once

#include <string>
#include <map>

#include <SDL.h>
#include <SDL_audio.h>
#include <SDL_mixer.h>

class AudioManager
{
public:
	static inline bool Init() { return Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == 0; }

	static inline void Destroy() { Mix_Quit(); }

	static Mix_Music* GetMusic(std::string fileName)
	{
		std::string audioPath = "assets\\audio\\";
		std::string path = SDL_GetBasePath() + audioPath + fileName;

		if (mMusic[path] == nullptr)
		{
			mMusic[path] = Mix_LoadMUS(path.c_str());
		}

		return mMusic[path];
	}

	static Mix_Chunk* GetSFX(std::string& fileName)
	{
		std::string audioPath = "assets\\audio\\";
		std::string path = SDL_GetBasePath() + audioPath + fileName;

		if (mSFX[path] == nullptr)
		{
			mSFX[path] = Mix_LoadWAV(path.c_str());
		}

		return mSFX[path];
	}

	static void PlayMusic(std::string fileName, int loops = -1)
	{
		Mix_PlayMusic(GetMusic(fileName), loops);
	}

	static void PauseMusic()
	{
		if (Mix_PlayingMusic() != 0)
		{
			Mix_PauseMusic();
		}
	}

	static void ResumeMusic()
	{
		if (Mix_PausedMusic() != 0)
		{
			Mix_ResumeMusic();
		}
	}

	static inline void FadeInMusic(std::string fileName, int fadeInTimeMilliseconds, int loop = -1) { Mix_FadeInMusic(GetMusic(fileName), loop, fadeInTimeMilliseconds); }
	static inline void FadeOutMusic(int fadeoutTimeMilliseconds) { if(Mix_PlayingMusic()) Mix_FadeOutMusic(fadeoutTimeMilliseconds); }

	static inline void PlaySFX(std::string fileName, int loops = 0, int channel = -1) { Mix_PlayChannel(channel, GetSFX(fileName), loops); }
	static inline void SetMasterVolume(int maxVolume = 100) { int volume = (128 * maxVolume) / 100; Mix_MasterVolume(volume); Mix_VolumeMusic(volume); }
	static inline void SetSFXVolume(int channel = -1, int maxVolume = 100) { int volume = (128 * maxVolume) / 100; Mix_Volume(channel, volume); }
	static inline void SetMusicVolume(int maxVolume = 100) { int volume = (128 * maxVolume) / 100; Mix_VolumeMusic(volume); }

	static SDL_AudioSpec wavSpec;
	static Uint32 wavLength;
	static Uint8* wavBuffer;
	static SDL_AudioDeviceID deviceID;

	static std::map<std::string, Mix_Music*> mMusic;
	static std::map<std::string, Mix_Chunk*> mSFX;
};