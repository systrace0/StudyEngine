#include "Renderer/Mesh.h"

namespace trace
{
	Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<U32>& indices)
		// By the time it reaches the body - vbo and ebo data is on the GPU via their constructors
		: m_vbo(vertices.data(), vertices.size() * sizeof(Vertex))
		, m_ebo(indices.data(), static_cast<U32>(indices.size()))
		, m_indexCount(static_cast<U32>(indices.size()))
	{
		ASSERT(m_vao.id() != 0, "VAO failed to create");
		ASSERT(m_vbo.id() != 0, "VBO failed to create");
		ASSERT(m_ebo.id() != 0, "EBO failed to create");

		m_vao.bind();
		m_vbo.bind();
		m_ebo.bind();

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		glEnableVertexAttribArray(0);																		 // Enable slot 0
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));	 // Color - starts 12 bytes later
		glEnableVertexAttribArray(1);																		 // Enable slot 1
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords)); // Texture - starts 12 bytes later
		glEnableVertexAttribArray(2);																		 // Enable slot 2
	}

	void Mesh::draw() const
	{
		ASSERT(m_vao.id() != 0, "Drawing invalid Mesh");
		m_vao.bind();
		glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, nullptr);
		m_vao.unbind();
	}
}