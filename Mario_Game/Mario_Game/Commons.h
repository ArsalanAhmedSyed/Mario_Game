#pragma once
#include <SDL.h>

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

enum SCREENS
{
	SCREEN_CONTROLS,
	SCREEN_MENU,
	SCREEN_LEVEL1,
	SCREEN_LEVEL2,
	SCREEN_GAMEOVER,
	SCREEN_HIGHSCOORES
};

enum FACING
{
	FACING_LEFT,
	FACING_RIGHT
};

enum AUDIO
{
	GAMEOVER,
	POWBLOCK,
	JUMP,
	DEATH,
	COIN,
};

enum MUSIC
{
	MENU_MUSIC,
	GAMEPLAY_MUSIC,
	STOP_MUSIC
};