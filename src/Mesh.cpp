#include "Mesh.h"

namespace trace
{
	Mesh::Mesh(const F32* vertices, U32 vertexSize, const U32* indices, U32 indexCount)
		// By the time it reaches the body - vbo and ebo data is on the GPU via their constructors
		: m_vbo(vertices, vertexSize)
		, m_ebo(indices, indexCount)
		, m_indexCount(indexCount)
	{
		ASSERT(m_vao.id() != 0, "VAO failed to create");
		ASSERT(m_vbo.id() != 0, "VBO failed to create");
		ASSERT(m_ebo.id() != 0, "EBO failed to create");

		m_vao.bind();
		m_vbo.bind();
		m_ebo.bind();

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(F32), (void*)0);					// Position
		glEnableVertexAttribArray(0);																// Enable slot 0
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(F32), (void*)(3 * sizeof(F32))); // Color - starts 12 bytes later
		glEnableVertexAttribArray(1);
	}

	void Mesh::draw() const
	{
		ASSERT(m_vao.id() != 0, "Drawing invalid Mesh");
		m_vao.bind();
		glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, nullptr);
		m_vao.unbind();
	}
}