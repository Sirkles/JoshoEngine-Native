#include "stdafx.h"

#include "Song.h"
#include "Game.h"

using namespace JoshoEngine;

Song::Song(const char* file)
{
	Game::fmodSystemInstance()->createStream(file, FMOD_DEFAULT, NULL, &this->soundInstance);
}

void Song::play()
{
	Game::fmodSystemInstance()->playSound(this->soundInstance, NULL, false, &this->channel);
}

void Song::stop()
{
	this->channel->stop();
}
