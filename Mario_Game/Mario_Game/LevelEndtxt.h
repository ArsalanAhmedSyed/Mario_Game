#ifndef _LEVELENDTXT_H
#define _LEVELENDTXT_H

#include "TextBase.h"
class LevelEndtxt : public TextBase
{
public:
	LevelEndtxt(SDL_Renderer* renderer);
	~LevelEndtxt();

	void Loadtxt() override;
};

#endif // !_LEVELENDTXT_H



