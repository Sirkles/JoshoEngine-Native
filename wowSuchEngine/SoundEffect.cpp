#include "stdafx.h"

#include "SoundEffect.h"
#include "Game.h"

using namespace JoshoEngine;

SoundEffect::SoundEffect(const char* file)
{
	Game::fmodSystemInstance()->createSound(file, FMOD_DEFAULT, NULL, &this->soundInstance);
}

void SoundEffect::unload()
{
	this->soundInstance->release();
}

void SoundEffect::setAttributes()
{

}

void SoundEffect::play()
{
	// Can't get address of function that retuns pointer, wtf?!
	FMOD::Channel* gameChannel = Game::fmodChannelInstance();

	// Tell the global sound system to play the sound using the global audio channel.
	Game::fmodSystemInstance()->playSound(this->soundInstance, NULL, false, &gameChannel);
}

void SoundEffect::play(SoundEffect* sound)
{
	sound->play();
}
