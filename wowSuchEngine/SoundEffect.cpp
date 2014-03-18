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
