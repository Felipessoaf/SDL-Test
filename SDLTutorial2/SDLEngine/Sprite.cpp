#include "Sprite.h"
#include "Vertex.h"
#include "ResourceManager.h"

#include <cstddef>

namespace SDLEngine
{
	Sprite::Sprite()
		: _vboID(0)
	{
	}

	Sprite::~Sprite()
	{
		if (_vboID != 0)
		{
			glDeleteBuffers(1, &_vboID);
		}
	}

	void Sprite::Init(float x, float y, float width, float height, std::string texturePath)
	{
		_x = x;
		_y = y;
		_width = width;
		_height = height;

		_texture = ResourceManager::GetTexture(texturePath);

		if (_vboID == 0)
		{
			glGenBuffers(1, &_vboID);
		}

		Vertex vertexData[6];

		//first triangle
		vertexData[0].SetPosition(x + width, y + height);
		vertexData[0].SetUV(1.0f, 1.0f);

		vertexData[1].SetPosition(x, y + height);
		vertexData[1].SetUV(0.0f, 1.0f);

		vertexData[2].SetPosition(x, y);
		vertexData[2].SetUV(0.0f, 0.0f);

		//second triangle
		vertexData[3].SetPosition(x, y);
		vertexData[3].SetUV(0.0f, 0.0f);

		vertexData[4].SetPosition(x + width, y);
		vertexData[4].SetUV(1.0f, 0.0f);

		vertexData[5].SetPosition(x + width, y + height);
		vertexData[5].SetUV(1.0f, 1.0f);

		for (int i = 0; i < 6; i++)
		{
			vertexData[i].SetColor(255, 0, 255, 255);
		}

		vertexData[1].SetColor(0, 0, 255, 255);
		vertexData[4].SetColor(0, 255, 0, 255);

		glBindBuffer(GL_ARRAY_BUFFER, _vboID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Sprite::Draw()
	{
		glBindTexture(GL_TEXTURE_2D, _texture.id);

		glBindBuffer(GL_ARRAY_BUFFER, _vboID);

		glEnableVertexAttribArray(0);

		//position attribute pointer
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		//color attribute pointer
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
		//uv attribute pointer
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		glDrawArrays(GL_TRIANGLES, 0, 6);

		glDisableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}