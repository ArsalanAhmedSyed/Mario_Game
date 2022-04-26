#include "SoundEffect.h"

SoundEffect::SoundEffect() 
{
	m_sound_effect = nullptr;
}

SoundEffect::~SoundEffect()
{
	if (m_sound_effect != nullptr)
	{
		Mix_FreeChunk(m_sound_effect);
	}
}

bool SoundEffect::LoadFromFile(string path)
{
	bool success = true;

	if (m_sound_effect != nullptr)
	{
		Mix_FreeChunk(m_sound_effect);
		m_sound_effect = nullptr;
	}

	m_sound_effect = Mix_LoadWAV(path.c_str());
	if (m_sound_effect == nullptr)
	{
		cout << "Failed to load sound effect. Error: %s " << Mix_GetError() << endl;
		success = false;
	}

	return success;
}

void SoundEffect::Play(AUDIO sound)
{
	if (sound == JUMP)
	{
		LoadFromFile("Audio/Jump.wav");
		Mix_PlayChannel(-1, m_sound_effect, 0);
	}

	if (sound == DEATH)
	{
		LoadFromFile("Audio/Death.wav");
		Mix_PlayChannel(-1, m_sound_effect, 0);
	}

	if (sound == POWBLOCK)
	{
		LoadFromFile("Audio/PowBlock.wav");
		Mix_PlayChannel(-1, m_sound_effect, 0);
	}

	if (sound == COIN)
	{
		LoadFromFile("Audio/Coin.wav");
		Mix_PlayChannel(-1, m_sound_effect, 0);
	}
}