#pragma once

#include <string>
#include <vector>

namespace pandaGraphics
{
	namespace GL
	{
		enum class DataType : unsigned int
		{
			FLOAT = 0x1406
		};

		enum class DrawMode : unsigned int
		{
			TRIANGLES = 0x0004
		};

		class Shader;
		class Uniform;
		class VertexBuffer;

		class Program
		{
		public:
			Program();

			Program(const Program &) = delete;
			Program & operator=(const Program &) = delete;

			void Attach(const Shader & shader);
			bool Link();

			int FindAttribute(const std::string & name);
			Uniform FindUniform(const std::string & name) const;

			std::string GetErrorLog() const;
			unsigned int GetHandle() const { return m_handle; }

		private:
			unsigned int m_handle;
		};

		class Shader
		{
		public:
			enum class Type
			{
				FRAGMENT = 0x8B30,
				VERTEX
			};

			Shader(Type type);

			// delete copy-constructor and copy-assignment
			Shader(const Shader &) = delete;
			Shader & operator=(const Shader &) = delete;

			void Upload(const std::string & source);
			bool Compile();

			std::string GetErrorLog() const;
			unsigned int GetHandle() const;

		private:
			unsigned int m_handle;
		};

		class Texture
		{
		public:
			Texture();

		private:
			unsigned int m_handle;
		};

		class Uniform
		{
		public:

		private:
			Uniform(const Program & program, int index);

			const Program & m_program;
			int m_index;

			friend class Program;
		};

		class VertexArray
		{
		public:
			struct AttribPointerInfo
			{
				int size;
				DataType type;
				int stride;
				intptr_t offset;
			};

			VertexArray();

			void SetAttribPointer(int attrib, const VertexBuffer & buffer, const AttribPointerInfo & info);

			inline unsigned int GetHandle() const { return m_handle; }

		private:
			unsigned int m_handle;
		};

		class VertexBuffer
		{
		public:
			VertexBuffer();
			VertexBuffer(const VertexBuffer &) = delete;
			VertexBuffer(VertexBuffer &&) noexcept;

			~VertexBuffer();

			template<class T>
			inline void Upload(const std::vector<T> & data)
			{
				Upload(reinterpret_cast<const void *>(&data[0]), static_cast<int>(sizeof(T) * data.size()));
			}

			void Upload(const void * data, int size);

			VertexBuffer & operator=(const VertexBuffer &) = delete;
			VertexBuffer & operator=(VertexBuffer &&) noexcept;

			inline unsigned int GetHandle() const { return m_handle; }

		private:
			unsigned int m_handle;
		};

		void Load();

		void UseProgram(const Program & program);
		const Program * GetCurrentProgram();

		void DrawArrays(const VertexArray & array, DrawMode mode, int first, int count);		
	}
}

#ifdef __cplusplus
extern "C" {
#endif



#ifdef __cplusplus
}
#endif