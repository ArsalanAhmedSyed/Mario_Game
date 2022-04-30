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

	void PlayMusic(MUSIC music);

private:
	bool LoadFromFile(string path);
	Mix_Chunk* m_sound_effect;

	bool LoadMusicFile(string music_path);
	Mix_Music* m_music;
};

#endif // _SOUNDEFFECT


