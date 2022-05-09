#include "CharacterMario.h"


CharacterMario::CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map,int frames) : Character(renderer, imagePath, start_position, map, frames) {}

CharacterMario::~CharacterMario() {}

void CharacterMario::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			m_moving_left = true;
			break;
		case SDLK_RIGHT:
			m_moving_right = true;
			break;
		case SDLK_UP:
			if (!m_kill_player)
			{
				Jump();
				if (m_play_jump_audio)
				{
					m_sound->Play(JUMP);
				}
			}
			break;
		}
		break;

	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			m_moving_left = false;
			break;
		case SDLK_RIGHT:
			m_moving_right = false;
		}
		break;
	}

	Character::Update(deltaTime, e);
}
