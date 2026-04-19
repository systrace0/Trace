#pragma once

#include <glad/glad.h>
#include <cstdint>

namespace engine
{
	class IndexBuffer
	{
	public:
		IndexBuffer(const uint32_t* data, size_t size);
		~IndexBuffer();

		IndexBuffer(const IndexBuffer&) = delete;
		IndexBuffer& operator=(const IndexBuffer&) = delete;

		IndexBuffer(IndexBuffer&& other) noexcept;
		IndexBuffer& operator=(IndexBuffer&& other) noexcept;

		void bind() const;
		void unbind() const;

	private:
		GLuint m_id{ 0 };
	};
}