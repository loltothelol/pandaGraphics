#include "../include/pandaGraphics/gl.h"

#include <stdexcept>
#include <string>

#include <glad/glad.h>
#include <glfw/glfw3.h>

static void CheckGLErrors()
{
	switch (glGetError())
	{
	case GL_NO_ERROR:
		break;

	case GL_INVALID_ENUM:
		throw std::logic_error("Invalid enum.");

	case GL_INVALID_VALUE:
		throw std::logic_error("Invalid value.");

	case GL_INVALID_OPERATION:
		throw std::logic_error("Invalid operation.");

	default:
		throw std::logic_error("Unknown error.");
	}
}

namespace PG = pandaGraphics;
namespace PGL = PG::GL;

/*
	class PG::Shader implementation
*/

PGL::Shader::Shader(Type type)
{
	m_handle = glCreateShader(static_cast<GLenum>(type));
	if (m_handle == 0) 
		throw std::runtime_error("Failed to create shader object.");
}

void PGL::Shader::Upload(const std::string & source)
{
	const char * data = source.data();
	int length = static_cast<int>(source.length());
	glShaderSource(m_handle, 1, &data, &length);
}

bool PGL::Shader::Compile()
{
	glCompileShader(m_handle);

	/* check compilation result */
	GLint compileStatus;
	glGetShaderiv(m_handle, GL_COMPILE_STATUS, &compileStatus);

	return compileStatus;
}

std::string PGL::Shader::GetErrorLog() const
{
	GLint infoLogLength;
	glGetShaderiv(m_handle, GL_INFO_LOG_LENGTH, &infoLogLength);

	char * infoLogBuffer = new char[infoLogLength];
	glGetShaderInfoLog(m_handle, infoLogLength, NULL, infoLogBuffer);

	std::string infoLog(infoLogBuffer, infoLogLength);
	delete[] infoLogBuffer;

	return infoLog;
}

unsigned int PGL::Shader::GetHandle() const
{
	return m_handle;
}

/*
	class PG::Program implementation
*/

PGL::Program::Program()
{
	m_handle = glCreateProgram();
	if (m_handle == 0) 
		throw std::runtime_error("Failed to create program object.");
}

void PGL::Program::Attach(const Shader & shader)
{
	glAttachShader(m_handle, shader.GetHandle());
	if (glGetError() == GL_INVALID_OPERATION)
		throw std::logic_error("Shader is already attached to program.");
}

bool PGL::Program::Link()
{
	glLinkProgram(m_handle);

	/* check link status */
	GLint linkStatus;
	glGetProgramiv(m_handle, GL_LINK_STATUS, &linkStatus);

	return linkStatus;
}

std::string PGL::Program::GetErrorLog() const
{
	GLint infoLogLength;
	glGetProgramiv(m_handle, GL_INFO_LOG_LENGTH, &infoLogLength);

	char * infoLogBuffer = new char[infoLogLength];
	glGetProgramInfoLog(m_handle, infoLogLength, NULL, infoLogBuffer);

	std::string infoLog(infoLogBuffer, infoLogLength);
	delete[] infoLogBuffer;

	return infoLog;
}

/*
	class pandaGraphics::Storage::VertexArray
*/

PGL::VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_handle);
}

void PGL::VertexArray::SetAttribPointer(int attrib, const VertexBuffer & buffer, const AttribPointerInfo & info)
{
	/* bind necessary state */
	glBindVertexArray(m_handle);
	glBindBuffer(GL_ARRAY_BUFFER, buffer.GetHandle());

	/* setup the pointer for the attribute array */
	glVertexAttribPointer(attrib, info.size, static_cast<GLenum>(info.type), GL_FALSE, info.stride, reinterpret_cast<const void *>(info.offset));
	CheckGLErrors();

	/* enable the attribute array */
	glEnableVertexAttribArray(attrib);

	/* unbind state */
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

/*
	class pandaGraphics::Storage::VertexBuffer
*/

PGL::VertexBuffer::VertexBuffer()
{
	glGenBuffers(1, &m_handle);
}

PGL::VertexBuffer::VertexBuffer(VertexBuffer && other) noexcept
{
	m_handle = std::exchange(other.m_handle, 0);
}

PGL::VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_handle);
}

void PGL::VertexBuffer::Upload(const void * data, int size)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_handle);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

auto PGL::VertexBuffer::operator=(VertexBuffer && other) noexcept -> VertexBuffer &
{
	m_handle = std::exchange(other.m_handle, 0);
	return *this;
}

/*
	namespace PG functions
*/

static thread_local const PGL::Program * g_currentProgram = nullptr;

void PGL::Load()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		throw std::runtime_error("Failed to load OpenGL functions!");

	//std::cout << "Successfully loaded OpenGL functions!" << std::endl;
}

void PGL::UseProgram(const Program & program)
{
	if (g_currentProgram != &program)
		glUseProgram(program.GetHandle());
	g_currentProgram = &program;
}

auto PGL::GetCurrentProgram() -> const Program *
{
	return g_currentProgram;
}

void PGL::DrawArrays(const VertexArray & array, DrawMode mode, int first, int count)
{
	glBindVertexArray(array.GetHandle());
	glDrawArrays(static_cast<GLenum>(mode), first, count);
	glBindVertexArray(0);
}