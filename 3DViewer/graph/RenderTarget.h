#ifndef RENDERTARGET_H
#define RENDERTARGET_H

#include"Drawable.h"
#include"Vertex.h"
#include<vector>

using std::vector;

namespace rtx
{
	namespace graph
	{

		class Mesh;

		class RenderTarget
		{
		public:

			void Draw(const Drawable& drawable)const;

			void Draw(vector<Vertex> vertices, int vertexSize, unsigned int vao)const;

		};
	}
}

#endif // !RENDERTARGET_H
