#pragma once

namespace pandaGraphics
{
	//
	//	Basic structures
	//

	struct Point
	{
		float x, y;
	};

	struct Color
	{
		float r, g, b, a;
	};

	struct Vertex
	{
		Point xy, uv;
		Color color;
	};

	//
	//	Shape primitives
	//

	struct Triangle
	{
		Vertex vertices[3];
	};

	struct Quad
	{
		Vertex vertices[4];
	};

	struct Rect
	{
		Point min, max;
		Color color;
	};

	//
	//	Constructors
	//

	Quad CreateQuadFromRect(const Rect & rect);
}