#include "TextRenderer.h"

TextRenderer::TextRenderer(SDL_Renderer* renderer)
{
	m_renderer = renderer;
}
TextRenderer::~TextRenderer()
{
	m_renderer = nullptr;

	//Delete texture
	SDL_DestroyTexture(m_texture);
	m_texture = nullptr;
}

void TextRenderer::Render(int x, int y)
{
	text_rect.x = x;
	text_rect.y = y;
	
	SDL_RenderCopy(m_renderer, m_texture, nullptr, &text_rect);
}

bool TextRenderer::LoadFont(const string path, int font_size, const string message, SDL_Color colour)
{
	//Get Font file
	m_font = TTF_OpenFont(path.c_str(), font_size);
	if (m_font == nullptr)
	{
		cout << "failed to open font! TTF_Error: %s\n" << TTF_GetError();
	}

	//Stor the TTF Text render inside surface
	SDL_Surface* text_surface = TTF_RenderText_Solid(m_font, message.c_str(), colour);
	if (text_surface == nullptr)
	{
		cout << "Failed to create surface! TTF_Error: %s\n" << TTF_GetError();
	}
	else
	{
		//Create Texture from the surface
		m_texture = SDL_CreateTextureFromSurface(m_renderer, text_surface);
		if (m_texture == nullptr)
		{
			cout << "Failed to create texture! TTF_Error: %s\n" << TTF_GetError();
		}
	}

	//Close the font file
	TTF_CloseFont(m_font);
	SDL_FreeSurface(text_surface);

	//Set Attributes of the font texture
	SDL_QueryTexture(m_texture, nullptr, nullptr, &text_rect.w, &text_rect.h);

	return m_texture != nullptr;
}