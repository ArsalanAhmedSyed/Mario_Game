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

	void Play(AUDIO sound);

private:
	bool LoadFromFile(string path);

	Mix_Music* m_music;
	Mix_Chunk* m_sound_effect;
};

#endif // _SOUNDEFFECT


