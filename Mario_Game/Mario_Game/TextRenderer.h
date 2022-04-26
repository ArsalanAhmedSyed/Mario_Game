#ifndef _TextRenderer_H
#define _TextRenderer_H

#include <SDL_ttf.h>
#include <SDL.h>
#include <string>
#include <iostream>

using namespace std;

class TextRenderer
{
public:
	TextRenderer(SDL_Renderer* renderer);
	~TextRenderer();

	void Render(int x, int y);

	bool LoadFont(const string path, int font_size, const string message, SDL_Color colour);

private:
	SDL_Renderer* m_renderer;
	SDL_Texture* m_texture;
	SDL_Rect text_rect;
	TTF_Font* m_font;
};

#endif // !_TextRenderer_H


