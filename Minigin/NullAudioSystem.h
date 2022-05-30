#pragma once
#include "AudioSystem.h"

namespace dae
{
	class NullAudioSystem final : public AudioSystem
	{
	public:
		void PlaySound(const std::string&) override;
		void CheckQueue() override;
	};
}

