#pragma once
#ifndef _TEXTURE2D_H
#define _TEXTURE2D_H

#include <SDL.h>
#include <string>
#include "Commons.h"

using namespace std;

class Texture2D
{
public:
	Texture2D(SDL_Renderer* renderer);
	~Texture2D();

	bool LoadFromFile(string path);
	void Free();
	void Render(Vector2D new_position, SDL_RendererFlip flip, double angle = 0.0);

	int GetWidth() { return m_Width; }
	int GetHeight() { return m_Height; }

private:

	SDL_Renderer* m_Renderer;
	SDL_Texture* m_Texture;

	int m_Width;
	int m_Height;
};

#endif // _TEXTURE2D_H


