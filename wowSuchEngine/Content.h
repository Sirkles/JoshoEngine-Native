#ifndef JOSHOENGINE_CONTENT_H_
#define JOSHOENGINE_CONTENT_H_

#include "JoshoEngine.h"

#include <string>

namespace JoshoEngine
{
	class Content
	{
	public:
		Content(std::string baseDirectory = "./")
		{
			this->directory = baseDirectory;

			if (this->directory.back() != '/')
			{
				this->directory += '/';
			}
		}

		template <typename T, typename ... Args>
		T* load(std::string fileName, Args ... args) const
		{
			return new T((this->directory + fileName).c_str(), args ...);
		}
	private:
		std::string directory;
	};
}

#endif
