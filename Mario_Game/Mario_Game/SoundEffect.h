#ifndef _SOUNDEFFECT
#define _SOUNDEFFECT

#include <SDL.h>
#include <SDL_Mixer.h>
#include <iostream>
#include <string>

#include "Commons.h"

using namespace std;

class SoundEffect
{
public:
	SoundEffect();
	~SoundEffect();

	bool LoadFromFile(string path);

	void Play(AUDIO jump);

private:
	Mix_Music* m_music;
	Mix_Chunk* m_jump_audio;

};

#endif // _SOUNDEFFECT


