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

void Song::pause()
{
	this->channel->setPaused(true);
}

void Song::stop()
{
	this->channel->stop();
}

void Song::setLoop(int loop)
{
	this->channel->setLoopCount(loop);
}

int Song::getLoop()
{
	int loops = 0;

	this->channel->getLoopCount(&loops);

	return loops;
}

bool Song::isPlaying()
{
	bool result = false;

	this->channel->isPlaying(&result);

	return result;
}

bool Song::isPaused()
{
	bool result = false;

	this->channel->getPaused(&result);

	return result;
}
