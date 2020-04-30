#pragma once

#include <memory>

namespace pandaIO
{
	template <typename T>
	class OutputStream
	{
	public:
		virtual void Write(const T &) = 0;
		virtual void Write(const std::vector<T> &) = 0;
	};

	template <typename T>
	class BufferedOutputStream : public OutputStream<T>
	{
	public:
		void Write(const T & element) override
		{
			m_buffer.push_back(element);
		}

		void Write(const std::vector<T> & elements) override
		{
			m_buffer.insert(m_buffer.end(), elements.begin(), elements.end());
		}

		void Flush()
		{
			m_stream->Write(m_buffer);
			m_buffer.clear();
		}

		const std::vector<T> & GetBuffer() const
		{
			return m_buffer;
		}

	private:
		std::vector<T> m_buffer;
		std::shared_ptr<OutputStream<T>> m_stream;
	};
}