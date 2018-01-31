//Audio.cpp
#include "Audio.h"
#include <string>

using namespace std;

Audio::Audio(bool load,bool menu)
{
	if(load)
	{
		loadMusic(menu);
		loadSounds();
	}
}


Audio::~Audio(void)
{
}


bool Audio::loadMusic(bool menu)
{
	string path;
	if(menu)
		path="data/soundtrack/SpaceExploration.ogg";
	else
		path="data/soundtrack/techno_space.ogg";

	if(!music.openFromFile(path))
		return false;
	music.setLoop(true);
	return true;
}


bool Audio::loadSounds()
{
	string name[T_COUNT]={"shot.wav","menu.wav","click.wav"};
	for(int i=0;i<T_COUNT;i++)
	{
		if(!buffer[i].loadFromFile("data/soundtrack/"+name[i]))
			return false;;
	}
	return true;
}


void Audio::playMusic()
{
	music.play();
}


void Audio::stopMusic()
{
	music.stop();
}


void Audio::playSound(SoundType type)
{
	sound.setBuffer(buffer[type]);
	sound.play();
}


void Audio::setVolume(bool mute)
{
	if(mute)
	{
		music.stop();
		music.setVolume(0);
		sound.setVolume(0);
	}
	else
	{
		music.play();
		music.setVolume(100);
		sound.setVolume(100);
	}
}