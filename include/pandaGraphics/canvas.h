#pragma once

#include <memory>
#include <vector>

#include "geom.h"
#include "gl.h"
#include "stream.h"

namespace pandaGraphics
{
	class Texture;

	class Canvas
	{
	public:
		using Stream = pandaIO::OutputStream<Triangle>;

	public:
		Canvas(const std::shared_ptr<Stream> & stream);

		void DrawTriangle(const Triangle & tri);
		void DrawQuad(const Quad & quad);
		void DrawRect(const Rect & rect);

	private:
		std::shared_ptr<Stream> m_stream;
	};
}