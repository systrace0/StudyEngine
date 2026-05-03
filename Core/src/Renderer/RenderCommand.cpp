#include "RenderCommand.h"
#include "VertexArray.h"

namespace trace
{
	void RenderCommand::setClearColor(F32 r, F32 g, F32 b, F32 a)
	{
		glClearColor(r, g, b, a);
	}

	void RenderCommand::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void RenderCommand::drawIndexed(const VertexArray& va)
	{
		ASSERT(va.id() != 0, "Drawing with invalid VertexArray");
		va.bind();
		glDrawElements(GL_TRIANGLES, va.indexCount(), GL_UNSIGNED_INT, nullptr);
		va.unbind();
	}
}
