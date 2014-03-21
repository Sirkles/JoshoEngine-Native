#ifndef JOSHOENGINE_SOUND_EFFECT_H_
#define JOSHOENGINE_SOUND_EFFECT_H_

#include "JoshoEngine.h"
#include <fmod.hpp>

namespace JoshoEngine
{
	class JOSHO_API SoundEffect
	{
	public:
		typedef struct
		{
			bool paused;
			bool loop;
			int loopTimes;
		} SoundAttributes;

		SoundEffect(const char* file);

		void unload();

		void setAttributes(SoundAttributes* attributes);

		void play();

		void stop();

		bool isPlaying();
	private:
		FMOD::Sound* soundInstance;
		FMOD::Channel* channel;
		SoundAttributes attributes;
	};
}

#endif
