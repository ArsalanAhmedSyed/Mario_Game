#include "Texture2D.h"
#include <iostream>
#include <SDL_image.h>

using namespace std;

Texture2D::Texture2D(SDL_Renderer* renderer)
{
	m_Renderer = renderer;

}

Texture2D::~Texture2D()
{
	//Free memory space
	Free();

	m_Renderer = nullptr;
}

void Texture2D::Free()
{
	//check if texture exist before removing
	if (m_Texture != nullptr)
	{
		SDL_DestroyTexture(m_Texture);
		m_Texture = nullptr;

		m_width = 0;
		m_height = 0;
	}
}

bool Texture2D::LoadFromFile(string path)
{
	//free existing texture
	Free();

	//Get Texture file
	SDL_Surface* p_Surface = IMG_Load(path.c_str());
	if (p_Surface == nullptr)
	{
		cout << "Unable to create texture from surface. IMG_Error: %s\n" << IMG_GetError();
	}
	else
	{
		SDL_SetColorKey(p_Surface, SDL_TRUE, SDL_MapRGB(p_Surface->format, 0, 0XFF, 0XFF));
		//Create Texture from surface
		m_Texture = SDL_CreateTextureFromSurface(m_Renderer, p_Surface);
		if (m_Texture == nullptr)
		{
			cout << "Unable to create texture from surface. IMG_Error: %s\n" << IMG_GetError();
		}
		else
		{
			m_width = p_Surface->w;
			m_height = p_Surface->h;
		}

		SDL_FreeSurface(p_Surface);
	}

	return m_Texture != nullptr;
}

void Texture2D::Render(Vector2D new_position, SDL_RendererFlip flip, double angle)
{
	//Create rendering location
	SDL_Rect renderLocation
	{
		renderLocation.x = new_position.x,
		renderLocation.y = new_position.y,
		renderLocation.w = m_width,
		renderLocation.h = m_height
	};

	//Render to screen
	SDL_RenderCopyEx(m_Renderer, m_Texture, nullptr, &renderLocation, angle, nullptr, flip);
}

int Texture2D::GetWidth() { return m_width; }
int Texture2D::GetHeight() { return m_height; }

void Texture2D::Render(SDL_Rect src_rect, SDL_Rect src_dest, SDL_RendererFlip flip, double angle)
{
	//Used to render characters/Objects in specific places
	SDL_RenderCopyEx(m_Renderer, m_Texture, &src_rect, &src_dest, angle, nullptr, flip);
}

void Texture2D::Render(Vector2D new_position, SDL_Rect clip, SDL_RendererFlip flip, double angle)
{
	//Used to render background for camera
	SDL_Rect m_render_location  { new_position.x, new_position.y, m_width, m_height };

	if (clip.w != NULL)
	{
		m_render_location.w = clip.w;
	}
	
	if (clip.y != NULL)
	{
		m_render_location.y = clip.y;
	}

	SDL_RenderCopyEx(m_Renderer, m_Texture, &clip, &m_render_location, angle, nullptr, flip);
}
