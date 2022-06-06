#pragma once
#include "AudioSystem.h"

namespace dae
{
	class NullAudioSystem final : public AudioSystem
	{
	public:
		NullAudioSystem() = default;
		~NullAudioSystem() override = default;

		NullAudioSystem(const NullAudioSystem& other) = delete;
		NullAudioSystem(NullAudioSystem&& other) noexcept = delete;
		NullAudioSystem& operator=(const NullAudioSystem& other) = delete;
		NullAudioSystem& operator=(NullAudioSystem&& other) noexcept = delete;

		void PlaySound(const std::string& filePath, bool looped, int volume = -1) override;
		void CheckQueue() override;
	};
}

