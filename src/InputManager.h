#ifndef InputManager_hpp
#define InputManager_hpp

#include <stdio.h>
#include "GLIncludes.h"
#include <glm/glm.hpp>
#include <vector>

namespace glRenderer // user-defined namespace (non-capitalized identifier)
{
	class InputManager
	{
	public:
		static void keyCallback(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods);

	};
}


#endif // !InputManager_hpp
