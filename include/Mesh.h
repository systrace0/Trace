#pragma once

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace engine
{
	class Mesh
	{
	public:
		Mesh(const F32* vertices, U32 vertexSize, const U32* indices, U32 indexCount);

		// Rule of Zero — VertexArray, VertexBuffer, IndexBuffer
		// all manage their own GPU resources via RAII.
		// No destructor, copy, or move needed here.

		void draw() const;

	private:
		VertexArray  m_vao;
		VertexBuffer m_vbo;
		IndexBuffer  m_ebo;
		U32 m_indexCount{ 0 };
	};
}