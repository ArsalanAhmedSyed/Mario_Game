#include "SoundEffect.h"

SoundEffect::SoundEffect() {}

SoundEffect::~SoundEffect()
{
	if (m_music != nullptr)
	{
		Mix_FreeMusic(m_music);
	}

	if (m_jump_audio != nullptr)
	{
		Mix_FreeChunk(m_jump_audio);
	}
}

bool SoundEffect::LoadFromFile(string path)
{
	bool success = true;
	m_jump_audio = Mix_LoadWAV("Audio/Jump.wav");
	if (m_music == nullptr)
	{
		cout << "Failed to load music. Error: %s " << Mix_GetError() << endl;
		success = false;
	}

	return success;
}

void SoundEffect::Play(AUDIO sound)
{
	if (sound == JUMP)
	{
		Mix_PlayChannel(-1, m_jump_audio, 0);
	}
}