#ifndef JOSHOENGINE_SOUND_EFFECT_H_
#define JOSHOENGINE_SOUND_EFFECT_H_

#include "JoshoEngine.h"
#include <fmod.hpp>

namespace JoshoEngine
{
	class JOSHO_API SoundEffect
	{
	public:
		SoundEffect(const char* file);

		void unload();

		void setAttributes();

		void play();

		static void play(SoundEffect* sound);
	private:
		FMOD::Sound* soundInstance;
	};
}

#endif
