#ifndef JOSHOENGINE_SONG_H_
#define JOSHOENGINE_SONG_H_

#include "JoshoEngine.h"
#include <fmod.hpp>

namespace JoshoEngine
{
	class JOSHO_API Song
	{
	public:
		Song(const char* file);

		void play();

		void pause();

		void stop();

		// -1 is infinite
		void setLoop(int loop);

		// -1 is infinite
		int getLoop();

		bool isPlaying();

		bool isPaused();
	private:
		FMOD::Sound* soundInstance;
		FMOD::Channel* channel;
	};
}

#endif
