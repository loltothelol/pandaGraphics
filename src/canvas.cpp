#include "../include/pandaGraphics/canvas.h"

#include <assert.h>
#include <stdlib.h>

#include "../include/pandaGraphics/texture.h"

#define MAX_TRIANGLE_COUNT 256

namespace PG = pandaGraphics;
using PGC = PG::Canvas;

//
//	Constructor(s) & destructor(s)
//

PGC::Canvas(const std::shared_ptr<Stream> & stream) :
	m_stream(stream)
{

}

// 
//	Shape drawing
//

void PGC::DrawTriangle(const PG::Triangle & triangle)
{
	//	write triangle to the stream
	m_stream->Write(triangle);
}

void PGC::DrawQuad(const PG::Quad & quad)
{
	PG::Vertex v1, v2, v3, v4;
	v1 = quad.vertices[0];
	v2 = quad.vertices[1];
	v3 = quad.vertices[2];
	v4 = quad.vertices[3];

	DrawTriangle({ v1, v2, v3 });
	DrawTriangle({ v3, v4, v1 });
}

void PGC::DrawRect(const PG::Rect & rect)
{
	DrawQuad(CreateQuadFromRect(rect));
}