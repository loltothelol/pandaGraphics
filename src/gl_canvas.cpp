#include "../include/pandaGraphics/gl_canvas.h"

#include <stdexcept>

namespace PG = pandaGraphics;
namespace PGL = PG::GL;

static const std::string VERTEX_SHADER_SOURCE =
"";

static const std::string FRAGMENT_SHADER_SOURCE =
"";

PGL::CanvasStream::CanvasStream()
{
	//
	//	storage setup
	//
	{
		VertexArray::AttribPointerInfo info;
		info.offset = 0;
		info.size = 4;
		info.stride = 0;
		info.type = GL::DataType::FLOAT;

		m_array.SetAttribPointer(0, m_buffer, info);
	}
	//
	//	rendering setup
	//
	{
		Shader vertShader(Shader::Type::VERTEX);
		vertShader.Upload(VERTEX_SHADER_SOURCE);
		if (!vertShader.Compile())
			throw std::runtime_error("Vertex shader compilation failed: " + vertShader.GetErrorLog());

		Shader fragShader(Shader::Type::FRAGMENT);
		fragShader.Upload(FRAGMENT_SHADER_SOURCE);
		if (!fragShader.Compile())
			throw std::runtime_error("Fragment shader compilation failed: " + fragShader.GetErrorLog());

		m_program.Attach(vertShader);
		m_program.Attach(fragShader);

		if (!m_program.Link())
			throw std::runtime_error("Program linking failed: " + m_program.GetErrorLog());
	}
}

void PGL::CanvasStream::Write(const std::vector<PG::Triangle> & tris)
{
	m_buffer.Upload(tris);
	UseProgram(m_program);
	DrawArrays(m_array, DrawMode::TRIANGLES, 0, static_cast<int>(tris.size()));
}

