#include "LevelMap.h"
#include "Texture2D.h"

LevelMap::LevelMap(int map[MAP_HEIGHT][MAP_WIDTH], SDL_Renderer* renderer)
{
	//Allocate memory for the level map
	m_map = new int* [MAP_HEIGHT];
	//Create rows and colums
	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		m_map[i] = new int[MAP_WIDTH];
	}
	
	//Populate the array
	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		for (unsigned int j = 0; j < MAP_WIDTH; j++)
		{
			m_map[i][j] = map[i][j];
		}
	}

	//Render platform texture
	m_platform = new Texture2D(renderer);
	if (!m_platform->LoadFromFile("Images/Platform.png"))
	{
		cout << "platform texture could not be loaded!" << endl;
	}	

	m_position = Vector2D(0, 0);
}

LevelMap::~LevelMap()
{
	//Delete the values insdie the array
	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		delete[] m_map[i];
	}
	delete[] m_map;
}

void LevelMap::DrawMap(SDL_Rect rect)
{
	SDL_Rect srcRect = { srcRect.x = 0, srcRect.y = 0, srcRect.w = PLATFORM_WIDTH, srcRect.h = PLATFORM_HEIGHT };
	SDL_Rect desRect = { 0, 0, desRect.w = TILE_WIDTH, desRect.h = TILE_HEIGHT };

	int type = 0;

	//Populate the array
	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		for (unsigned int j = 0; j < MAP_WIDTH; j++)
		{
			type = m_map[i][j];

			//Add ddistance between each platform
			desRect.x = j * 35 - rect.x;
			desRect.y = i * 32 - rect.y;

			//Render Texture places where there are once
			if (type == 1)
			{
				m_platform->Render(srcRect, desRect, SDL_FLIP_NONE);
			}
		}
	}
}

int LevelMap::GetTileAt(unsigned int h, unsigned int w)
{
	//Get the location of the tile
	if (h < MAP_HEIGHT && w < MAP_WIDTH)
	{
		return m_map[h][w];
	}

	return 0;
}

void LevelMap::ChangeTileAt(unsigned int row, unsigned int column, unsigned int new_value)
{
	//Change Tile at specific place
	m_map[column][row] = new_value;
}