#pragma once
#include "AudioSystem.h"

namespace dae
{
	class StandardAudioSystem final : public AudioSystem
	{
	public:
		StandardAudioSystem();
		~StandardAudioSystem() override;

		StandardAudioSystem(const StandardAudioSystem& other) = delete;
		StandardAudioSystem(StandardAudioSystem&& other) noexcept = delete;
		StandardAudioSystem& operator=(const StandardAudioSystem& other) = delete;
		StandardAudioSystem& operator=(StandardAudioSystem&& other) noexcept = delete;

		void PlaySound(const std::string& filePath, bool looped, int volume) override;
		void CheckQueue() override;
	};
}

