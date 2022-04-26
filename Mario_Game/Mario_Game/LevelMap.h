#ifndef _LEVELMAP_H
#define _LEVELMAP_H

#include <iostream>
#include "constants.h"
#include "SDL.h"

using namespace std;

class Texture2D;

class LevelMap
{
public:
	LevelMap(int map[MAP_HEIGHT][MAP_WIDTH], SDL_Renderer* renderer);
	~LevelMap();

	int GetTileAt(unsigned int h, unsigned int w);

	void ChangeTileAt(unsigned int row, unsigned int column, unsigned int new_value);

	void DrawMap();

private:
	int** m_map;

	SDL_Rect srcRect, desRect;

	Texture2D* m_platform;
};

#endif // !_LEVELMAP_H



