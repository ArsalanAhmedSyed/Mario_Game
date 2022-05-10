#ifndef _CHARACTER_H
#define _CHARACTER_H

#include <SDL.h>
#include <iostream>
#include <string>
#include "Commons.h"
#include "constants.h"
#include "Texture2D.h"
#include "SoundEffect.h"
#include "LevelMap.h"

using namespace std;

class LevelMap;

class Character
{
public:
	Character(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map, int frames);
	~Character();

	virtual void Render(SDL_Rect camera_rect);
	virtual void Update(float deltaTime, SDL_Event e);

	void SetPosition(Vector2D new_position) { m_position = new_position; }

	//Jump condition function
	bool IsJumping() { return m_jumping; }
	void CancelJump() { m_jumping = false; }

	Vector2D getPosition() { return m_position; }
	//Get Circle Collision
	Circle2D GetCollisionCircle() { return Circle2D(m_position.x, m_position.y, m_collision_radius); }
	//Get box Collision
	Rect2D getCollisionBox() { return Rect2D(m_position.x, m_position.y, m_texture->GetWidth()/ m_animation_frames, m_texture->GetHeight()); }

	virtual void Jump();

	void SetGrounded(bool grounded) { m_grounded = grounded; }

	//Check or change character alive condition
	void SetAlive(bool isAlive) { m_alive = isAlive; }
	bool GetAlive() { return m_alive; }

	//Kill Character or check condition
	void SetKill(bool isKilled) { m_kill_player = isKilled; }
	bool GetKill() { return m_kill_player; }

protected:
	SDL_Renderer* m_renderer;
	Vector2D m_position;
	Texture2D* m_texture;
	LevelMap* m_current_level_map;

	SoundEffect* m_sound;
	bool m_play_jump_audio;

	//keep everything in screen
	virtual void KeepOnScreen(float deltaTime);
	//Check if player collides with platform
	virtual void PlatformHit(float deltaTime, int Right_X, int LeftX, int central_Y);
	//Check Update character functions
	virtual void CharacterCondition(float deltaTime);

	//Character Central position
	int centralX_position;
	int centralY_position;

	//Character horizontal collision check veriables
	int RightX_position;
	int LeftX_position;

	//Character vertical collision check veraibles
	int foot_position;
	int head_position;

	//Character Dimensions
	virtual void CharacterDimension();
	//Sprite dimensions
	float m_single_sprite_w;
	float m_single_sprite_h;


	//Movement
	float m_movement_speed;
	bool m_moving_left;
	bool m_moving_right;
	//Movement Function
	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);

	//Jump
	bool m_can_jump;
	bool m_jumping;
	float m_jump_force;

	virtual void AddGravity(float deltaTime);

	//Collision
	float m_collision_radius;

	//kill Character
	float m_kill_timer;
	bool m_alive;	
	bool m_kill_player;

	//Spirte animation
	FACING m_facing_direction;
	int m_animation_frames;
	bool m_jump_Anim;
	int m_current_frame;
	float m_frame_delay;
	//Animation function
	virtual void DefaultAnimation(float deltaTime);

	bool m_grounded;

private:
};

#endif // !_CHARACTER_H



