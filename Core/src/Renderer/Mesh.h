#pragma once

#include "Renderer/VertexArray.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"

#include "Renderer/Vertex.h"

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