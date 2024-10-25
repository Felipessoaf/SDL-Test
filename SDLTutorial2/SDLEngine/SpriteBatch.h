#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

#include "Vertex.h"

namespace SDLEngine
{
	enum class GlyphSortType
	{
		NONE,
		FRONT_TO_BACK,
		BACK_TO_FRONT,
		TEXTURE
	};

	struct Glyph 
	{
		GLuint Texture;
		float Depth;

		Vertex TopLeft;
		Vertex BottomLeft;
		Vertex TopRight;
		Vertex BottomRight;
	};

	class RenderBatchObj
	{
	public:
		RenderBatchObj (GLuint offset, GLuint numVertices, GLuint texture) :
			Offset(offset),
			NumVertices(numVertices),
			Texture(texture)
		{

		}

		GLuint Offset;
		GLuint NumVertices;
		GLuint Texture;
	};

	class SpriteBatch
	{
	public:
		SpriteBatch();
		~SpriteBatch();

		void Init();

		void Begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
		void End();

		void Draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color);
		void RenderBatch();

	private:
		void CreateRenderBatches();
		void CreateVertexArray();
		void SortGlyphs();

		static bool CompareFrontToBack(Glyph* a, Glyph* b);
		static bool CompareBackToFront(Glyph* a, Glyph* b);
		static bool CompareTexture(Glyph* a, Glyph* b);

		GLuint _vbo;
		GLuint _vao;

		GlyphSortType _sortType;

		std::vector<Glyph*> _glyphs;
		std::vector<RenderBatchObj> _renderBatches;
	};
}