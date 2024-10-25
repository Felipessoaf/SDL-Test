#include "SpriteBatch.h"

#include <algorithm>

namespace SDLEngine
{
	SpriteBatch::SpriteBatch() :
		_vbo(0),
		_vao(0)
	{
	}

	SpriteBatch::~SpriteBatch()
	{
	}

	void SpriteBatch::Init()
	{
		CreateVertexArray();
	}

	void SpriteBatch::Begin(GlyphSortType sortType)
	{
		_sortType = sortType;
		_renderBatches.clear();
		for (int i = 0; i < _glyphs.size(); i++)
		{
			delete _glyphs[i];
		}
		_glyphs.clear();
	}

	void SpriteBatch::End()
	{
		SortGlyphs();
		CreateRenderBatches();
	}

	void SpriteBatch::Draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color)
	{
		Glyph* newGlyph = new Glyph();
		newGlyph->Texture = texture;
		newGlyph->Depth = depth;

		newGlyph->TopLeft.color = color;
		newGlyph->TopLeft.SetPosition(destRect.x, destRect.y + destRect.w);
		newGlyph->TopLeft.SetUV(uvRect.x, uvRect.y + uvRect.w);

		newGlyph->BottomLeft.color = color;
		newGlyph->BottomLeft.SetPosition(destRect.x, destRect.y);
		newGlyph->BottomLeft.SetUV(uvRect.x, uvRect.y);

		newGlyph->BottomRight.color = color;
		newGlyph->BottomRight.SetPosition(destRect.x + destRect.z, destRect.y);
		newGlyph->BottomRight.SetUV(uvRect.x + uvRect.z, uvRect.y);

		newGlyph->TopRight.color = color;
		newGlyph->TopRight.SetPosition(destRect.x + destRect.z, destRect.y + destRect.w);
		newGlyph->TopRight.SetUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

		_glyphs.push_back(newGlyph);
	}

	void SpriteBatch::RenderBatch()
	{
		glBindVertexArray(_vao);

		for (int i = 0; i < _renderBatches.size(); i++)
		{
			glBindTexture(GL_TEXTURE_2D, _renderBatches[i].Texture);
			glDrawArrays(GL_TRIANGLES, _renderBatches[i].Offset, _renderBatches[i].NumVertices);
		}

		glBindVertexArray(0);
	}

	void SpriteBatch::CreateRenderBatches()
	{
		std::vector<Vertex> vertices;
		vertices.resize(_glyphs.size() * 6);

		if (_glyphs.empty())
		{
			return;
		}

		int offset = 0;
		int currentVertex = 0;
		_renderBatches.emplace_back(offset, 6, _glyphs[0]->Texture);
		vertices[currentVertex++] = _glyphs[0]->TopLeft;
		vertices[currentVertex++] = _glyphs[0]->BottomLeft;
		vertices[currentVertex++] = _glyphs[0]->BottomRight;
		vertices[currentVertex++] = _glyphs[0]->BottomRight;
		vertices[currentVertex++] = _glyphs[0]->TopRight;
		vertices[currentVertex++] = _glyphs[0]->TopLeft;
		offset += 6;

		for (int currentGlyph = 1; currentGlyph < _glyphs.size(); currentGlyph++)
		{
			if (_glyphs[currentGlyph]->Texture != _glyphs[currentGlyph - 1]->Texture)
			{
				_renderBatches.emplace_back(offset, 6, _glyphs[currentGlyph]->Texture);
			}
			else
			{
				_renderBatches.back().NumVertices += 6;
			}

			vertices[currentVertex++] = _glyphs[currentGlyph]->TopLeft;
			vertices[currentVertex++] = _glyphs[currentGlyph]->BottomLeft;
			vertices[currentVertex++] = _glyphs[currentGlyph]->BottomRight;
			vertices[currentVertex++] = _glyphs[currentGlyph]->BottomRight;
			vertices[currentVertex++] = _glyphs[currentGlyph]->TopRight;
			vertices[currentVertex++] = _glyphs[currentGlyph]->TopLeft;
			offset += 6;
		}

		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void SpriteBatch::CreateVertexArray()
	{
		if (_vao == 0)
		{
			glGenVertexArrays(1, &_vao);
		}
		glBindVertexArray(_vao);

		if (_vbo == 0)
		{
			glGenBuffers(1, &_vbo);
		}
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		//position attribute pointer
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		//color attribute pointer
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
		//uv attribute pointer
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		glBindVertexArray(0);
	}

	void SpriteBatch::SortGlyphs()
	{
		switch (_sortType)
		{
			case SDLEngine::GlyphSortType::NONE:
				break;
			case SDLEngine::GlyphSortType::FRONT_TO_BACK:
				std::stable_sort(_glyphs.begin(), _glyphs.end(), CompareFrontToBack);
				break;
			case SDLEngine::GlyphSortType::BACK_TO_FRONT:
				std::stable_sort(_glyphs.begin(), _glyphs.end(), CompareBackToFront);
				break;
			case SDLEngine::GlyphSortType::TEXTURE:
				std::stable_sort(_glyphs.begin(), _glyphs.end(), CompareTexture);
				break;
			default:
				break;
		}
	}

	bool SpriteBatch::CompareFrontToBack(Glyph* a, Glyph* b)
	{
		return a->Depth < b->Depth;
	}

	bool SpriteBatch::CompareBackToFront(Glyph* a, Glyph* b)
	{
		return a->Depth > b->Depth;
	}

	bool SpriteBatch::CompareTexture(Glyph* a, Glyph* b)
	{
		return a->Texture < b->Texture;
	}
}