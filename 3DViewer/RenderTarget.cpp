#include"graph/RenderTarget.h"
#include"graph/Mesh.h"
namespace rtx
{
	namespace graph
	{
		void RenderTarget::Draw(const Drawable& drawable)const
		{
			drawable.Draw(*this);
		}

		void RenderTarget::Draw(vector<Vertex> vertices, int vertexSize, unsigned int vao)const
		{
			glBindVertexArray(vao);
			glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertices.size()));
		}

	}
}
