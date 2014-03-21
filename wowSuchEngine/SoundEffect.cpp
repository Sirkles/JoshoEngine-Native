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

	delete this->channel;
	delete this->soundInstance;
}

void SoundEffect::setAttributes(SoundAttributes* attributes)
{
	this->attributes = *attributes;
}

void SoundEffect::play()
{
	// Tell the global sound system to play the sound using the instance's audio channel.
	Game::fmodSystemInstance()->playSound(this->soundInstance, NULL, false, &this->channel);
}

void SoundEffect::stop()
{
	this->channel->stop();
}

bool SoundEffect::isPlaying()
{
	bool result = false;

	this->channel->isPlaying(&result);

	return result;
}
