#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace SDLEngine
{
	class Camera2D
	{
	public:
		Camera2D();
		~Camera2D();

		void Init(int screenWidth, int screenHeight);

		void Update();

		glm::vec2 ConvertScreenToWorld(glm::vec2 screenCoords);

		void SetPosition(const glm::vec2& newPosition) 
		{ 
			_position = newPosition; 
			_needsMatrixUpdate = true;
		}
		void SetScale(const float& newScale) 
		{ 
			_scale = newScale;
			_needsMatrixUpdate = true;
		}

		glm::vec2 GetPosition() { return _position; }
		float GetScale() { return _scale; }
		glm::mat4 GetCameraMatrix() { return _cameraMatrix; }

	private:
		int _screenWidth, _screenHeight;
		bool _needsMatrixUpdate;
		float _scale;
		glm::vec2 _position;
		glm::mat4 _cameraMatrix;
		glm::mat4 _orthoMatrix;
	};
}