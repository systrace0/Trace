#pragma once

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include "Vertex.h"

namespace trace
{
	class Mesh
	{
	public:
		Mesh(const std::vector<Vertex>& vertices, const std::vector<U32>& indices);
		void draw() const;
		// Rule of Zero — members handle themselves

	private:
		VertexArray  m_vao;
		VertexBuffer m_vbo;
		IndexBuffer  m_ebo;
		U32			 m_indexCount{ 0 };
	};
}