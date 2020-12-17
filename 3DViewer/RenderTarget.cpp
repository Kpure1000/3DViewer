#include"graph/RenderTarget.h"
#include"graph/Mesh.h"
#include"render//Shader.h"
namespace rtx
{
	using namespace render;
	namespace graph
	{
		void RenderTarget::Draw(const Drawable& drawable)const
		{
			RenderStates rts;
			drawable.Draw(*this, rts);
		}

		void RenderTarget::Draw(const Drawable& drawable, Shader& shader) const
		{
			RenderStates rts(shader);
			drawable.Draw(*this, rts);
		}

		void RenderTarget::Draw(const vector<Vertex>& vertices, unsigned int vao)const
		{
			glBindVertexArray(vao);
			glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertices.size()));
		}

		void RenderTarget::Draw(const vector<unsigned int>& indices, unsigned int vao)const
		{
			glBindVertexArray(vao);
			glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
		}
	}
}
