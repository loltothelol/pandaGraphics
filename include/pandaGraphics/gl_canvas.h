#pragma once

#include "canvas.h"
#include "gl.h"

namespace pandaGraphics
{
	namespace GL
	{
		class CanvasStream: public Canvas::Stream
		{
		public:
			CanvasStream();

			void Write(const std::vector<Triangle> & tris) override;

		private:
			VertexBuffer m_buffer;
			VertexArray m_array;
			Program m_program;
		};
	}
}