#pragma once

#include <GL/glew.h>

namespace SDLEngine
{
	struct Position
	{
		float x;
		float y;
	};

	struct Color
	{
		Color() {}
		Color(GLubyte r, GLubyte g, GLubyte b, GLubyte a) :
			r (r),
			g (g),
			b (b),
			a (a)
		{

		}

		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;
	};

	struct UV
	{
		float u;
		float v;
	};

	struct Vertex
	{
		Position position;
		Color color;
		UV uv;

		void SetPosition(float x, float y)
		{
			position.x = x;
			position.y = y;
		}

		void SetColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
		{
			color.r = r;
			color.g = g;
			color.b = b;
			color.a = a;
		}

		void SetUV(float u, float v)
		{
			uv.u = u;
			uv.v = v;
		}
	};
}