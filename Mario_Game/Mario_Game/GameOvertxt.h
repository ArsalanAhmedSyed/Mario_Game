#ifndef _GAMEOVERTXT_H
#define _GAMEOVERTXT_H

#include "TextBase.h"

class GameOvertxt :	public TextBase
{
public:
	GameOvertxt(SDL_Renderer* renderer);
	~GameOvertxt();

	void Loadtxt() override;

};

#endif // !_GAMEOVERTXT_H