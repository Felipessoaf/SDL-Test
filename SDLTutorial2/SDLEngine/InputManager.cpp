#include "InputManager.h"

namespace SDLEngine
{
	InputManager::InputManager() :
		_mouseCoords(0.0f)
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

	void InputManager::SetMouseCoords(float x, float y)
	{
		_mouseCoords.x = x;
		_mouseCoords.y = y;
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