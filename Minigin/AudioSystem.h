#pragma once
#include <mutex>
#include <queue>
#include "Audio.h"
#include <thread>

namespace dae
{
	class AudioSystem
	{
	public:
		AudioSystem() = default;
		virtual ~AudioSystem() = default;

		AudioSystem(const AudioSystem& other) = delete;
		AudioSystem(AudioSystem&& other) noexcept = delete;
		AudioSystem& operator=(const AudioSystem& other) = delete;
		AudioSystem& operator=(AudioSystem&& other) noexcept = delete;

		virtual void PlaySound(const std::string& filePath, bool looped, int volume = -1) = 0;
		virtual void CheckQueue() = 0;
	protected:
		std::vector<Audio*> m_PlayedSounds{};//This is to delete the sounds
		std::queue<Audio*> m_Sounds{};

		std::mutex m_Mutex;
		std::thread m_Thread;

		bool m_DoContinue{ true };
	};
}

