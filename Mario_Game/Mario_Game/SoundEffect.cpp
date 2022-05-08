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

	if (m_music != nullptr)
	{
		Mix_FreeMusic(m_music);
	}
}

bool SoundEffect::LoadFromFile(string path)
{
	if (m_sound_effect != nullptr)
	{
		Mix_FreeChunk(m_sound_effect);
		m_sound_effect = nullptr;
	}

	m_sound_effect = Mix_LoadWAV(path.c_str());
	if (m_sound_effect == nullptr)
	{
		cout << "Failed to load sound effect. Error: %s " << Mix_GetError() << endl;
	}

	return m_music != nullptr;
}

bool SoundEffect::LoadMusicFile(string music_path)
{
	if (m_music != nullptr)
	{
		if (Mix_PlayingMusic() == 1)
		{
			Mix_HaltMusic();
		}
	}

	m_music = Mix_LoadMUS(music_path.c_str());
	if (m_music == nullptr)
	{
		cout << "Failed to load music. Mix Error: %s" << Mix_GetError() << endl;
	}

	return m_music != nullptr;
}

void SoundEffect::PlayMusic(MUSIC music)
{
	switch (music)
	{
	case MENU_MUSIC:
		LoadMusicFile("Audio/MainMenuTheme.wav");
		Mix_PlayMusic(m_music, -1);
		break;
	case GAMEPLAY_MUSIC:
		LoadMusicFile("Audio/MarioMusic.wav");
		Mix_PlayMusic(m_music, -1);
		break;
	case STOP_MUSIC:
		Mix_HaltMusic();
		break;
	default:
		break;
	}
}

void SoundEffect::Play(AUDIO sound)
{
	switch (sound)
	{
	case JUMP:
		LoadFromFile("Audio/Jump.wav");
		Mix_PlayChannel(-1, m_sound_effect, 0);
		break;
	case DEATH:
		LoadFromFile("Audio/Death.wav");
		Mix_PlayChannel(-1, m_sound_effect, 0);
		break;
	case POWBLOCK:
		LoadFromFile("Audio/PowBlock.wav");
		Mix_PlayChannel(-1, m_sound_effect, 0);
		break;
	case COIN:
		LoadFromFile("Audio/Coin.wav");
		Mix_PlayChannel(-1, m_sound_effect, 0);
		break;
	case GAMEOVER:
		LoadFromFile("Audio/Death&GameOver.wav");
		Mix_PlayChannel(-1, m_sound_effect, 0);
		break;
	case LEVELEND:
		LoadFromFile("Audio/LevelEnd.wav");
		Mix_PlayChannel(-1, m_sound_effect, 0);
		break;
	default:
		break;
	}
}