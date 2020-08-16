#include "InputManager.h"
#include <iostream>

namespace glRenderer // user-defined namespace (non-capitalized identifier)
{
	void InputManager::keyCallback(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods)
	{
		if (_key == GLFW_KEY_E && _action == GLFW_PRESS)
		{
			std::cout << "You pressed 'E'" << std::endl;
		}
	}
}