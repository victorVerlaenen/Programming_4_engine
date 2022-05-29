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
		virtual void RegisterSound(const std::string& filePath) = 0;
		virtual void CheckQueue() = 0;
	protected:
		std::vector<Audio*> m_PlayedSounds{};
		std::queue<Audio*> m_Sounds{};

		std::mutex m_Mutex;
		std::thread m_Thread;

		bool m_DoContinue{ true };
	};
}

