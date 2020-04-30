#include "../include/pandaGraphics/geom.h"

namespace PG = pandaGraphics;

auto PG::CreateQuadFromRect(const Rect & rect) -> Quad
{
	const PG::Point & min = rect.min;
	const PG::Point & max = rect.max;
	const PG::Color & color = rect.color;

	PG::Point p1, p2, p3, p4;
	p1 = { min.x, min.y };
	p2 = { max.x, min.y };
	p3 = { max.x, max.y };
	p4 = { min.x, max.y };

	static const PG::Point uv1 = { 0, 0 }, uv2 = { 1, 0 }, uv3 = { 1, 1 }, uv4 = { 0, 1 };

	PG::Vertex v1, v2, v3, v4;
	v1 = { p1, uv1, color };
	v2 = { p2, uv2, color };
	v3 = { p3, uv3, color };
	v4 = { p4, uv4, color };

	return { v1, v2, v3, v4 };
}