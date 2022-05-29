#pragma once
#include "SDL_mixer.h"

namespace dae
{
	class Audio final
	{
	public:
		Audio(const std::string& filePath);
		~Audio();

		Audio(const Audio& other) = delete;
		Audio(Audio&& other) noexcept = delete;
		Audio& operator=(const Audio& other) = delete;
		Audio& operator=(Audio&& other) noexcept = delete;

		void Play() const;
		void Load() const;

		void SetVolume(int volume);
		int GetVolume() const;
		bool IsLoaded() const;
	private:
		class AudioImpl;
		AudioImpl* pImlp{ };
	};
	
	class Audio::AudioImpl
	{
	public:
		AudioImpl(const std::string& filePath);
		~AudioImpl();

		AudioImpl(const AudioImpl& other) = delete;
		AudioImpl(AudioImpl&& other) noexcept = delete;
		AudioImpl& operator=(const AudioImpl& other) = delete;
		AudioImpl& operator=(AudioImpl&& other) noexcept = delete;

		void Play();
		void Load();

		void SetVolume(int volume);
		int GetVolume() const;
		bool IsLoaded() const;
	private:
		Mix_Chunk* m_pMixChunk{};
		std::string m_FilePath;
	};
}