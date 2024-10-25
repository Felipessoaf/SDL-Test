#include "InputManager.h"

namespace SDLEngine
{
	InputManager::InputManager()
	{
	}

	InputManager::~InputManager()
	{
	}

	void InputManager::PressKey(unsigned int keyID)
	{
		_keyMap[keyID] = true;
	}

	void InputManager::ReleaseKey(unsigned int keyID)
	{
		_keyMap[keyID] = false;
	}

	bool InputManager::IsKeyPressed(unsigned int keyID)
	{
		auto it = _keyMap.find(keyID);

		if (it != _keyMap.end())
		{
			return it->second;
		}

		return false;
	}
}