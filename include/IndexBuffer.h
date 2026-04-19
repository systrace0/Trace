#pragma once

#include "Core.h"

#include <glad/glad.h>

namespace engine
{
	class IndexBuffer
	{
	public:
		IndexBuffer(const U32* data, size_t size);
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