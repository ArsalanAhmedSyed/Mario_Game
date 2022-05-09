#pragma once
#include <SDL.h>

//For positon
struct Vector2D
{
	float x;
	float y;

	Vector2D()
	{
		x = 0.0f;
		y = 0.0f;
	}

	Vector2D(float inital_x, float inital_y)
	{
		x = inital_x;
		y = inital_y;
	}

};

//For box Collision
struct Rect2D
{
	float x;
	float y;
	float width;
	float height;

	Rect2D()
	{
		x = 0.0f;
		y = 0.0f;
		width = 0.0f;
		height = 0.0f;
	}

	Rect2D(float x_pos, float y_pos, float width, float height)
	{
		x = x_pos;
		y = y_pos;
		this->width = width;
		this->height = height;
	}
};

//For raidus collision
struct Circle2D
{
	float x;
	float y;
	float radius;

	Circle2D()
	{
		x = 0.0f;
		y = 0.0f;
		radius = 0.0f;
	}

	Circle2D(float x_pos, float y_pos, float radius)
	{
		x = x_pos;
		y = y_pos;
		this->radius = radius;
	}
};

//List of screen
enum SCREENS
{
	SCREEN_SELECTION,
	SCREEN_CONTROLS,
	SCREEN_MENU,
	SCREEN_LEVEL1,
	SCREEN_LEVEL2,
};

//Direction of facing
enum FACING
{
	FACING_LEFT,
	FACING_RIGHT
};

//List of sound effects 
enum AUDIO
{
	LEVELEND,
	GAMEOVER,
	POWBLOCK,
	JUMP,
	DEATH,
	COIN,
};

//List of Music
enum MUSIC
{
	MENU_MUSIC,
	GAMEPLAY_MUSIC,
	STOP_MUSIC
};

//List of characters
enum CHARACTER
{
	MARIO,
	LUIGI
};