#include "MiniginPCH.h"
#include "Audio.h"

dae::Audio::Audio(const std::string& filePath)
{
	pImlp = new AudioImpl{ filePath };
}

dae::Audio::AudioImpl::AudioImpl(const std::string& filePath)
	:m_FilePath(filePath)
{

}

dae::Audio::~Audio()
{
	delete pImlp;
	pImlp = nullptr;
}

dae::Audio::AudioImpl::~AudioImpl()
{
	if(m_pMixChunk != nullptr)
	{
		Mix_FreeChunk(m_pMixChunk);
	}
}

void dae::Audio::Play() const
{
	pImlp->Play();
}

void dae::Audio::AudioImpl::Play()
{
	if(IsLoaded() == false)
	{
		return;
	}
	Mix_PlayChannel(-1, m_pMixChunk, 0);
}

void dae::Audio::Load() const
{
	pImlp->Load();
}


void dae::Audio::AudioImpl::Load()
{
	m_pMixChunk = Mix_LoadWAV(m_FilePath.c_str());
}

void dae::Audio::SetVolume(int volume)
{
	pImlp->SetVolume(volume);
}

void dae::Audio::AudioImpl::SetVolume(int volume)
{
	if(IsLoaded())
	{
		Mix_Volume(-1, volume);
	}
}

int dae::Audio::GetVolume() const
{
	return pImlp->GetVolume();
}

int dae::Audio::AudioImpl::GetVolume() const
{
	if(IsLoaded())
	{
		return Mix_VolumeChunk(m_pMixChunk, -1);
	}
	return 0;
}

bool dae::Audio::IsLoaded() const
{
	return pImlp->IsLoaded();
}

bool dae::Audio::AudioImpl::IsLoaded() const
{
	if(m_pMixChunk != nullptr)
	{
		return true;
	}
	return false;
}
