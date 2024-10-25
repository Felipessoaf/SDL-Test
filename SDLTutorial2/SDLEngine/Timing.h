#pragma once

namespace SDLEngine
{
	class FPSLimiter
	{
	public:
		FPSLimiter();

		void Init(float maxFPS);

		void SetMaxFPS(float maxFPS);

		void Begin();
		float End();

	private:
		void CalculateFPS();

		float _fps;
		float _maxFPS;
		float _frameTime;
		unsigned int _startTicks;
	};

}