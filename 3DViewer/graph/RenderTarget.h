#ifndef RENDERTARGET_H
#define RENDERTARGET_H

#include"Drawable.h"
#include"Vertex.h"
#include<vector>
#include"../render/Shader.h"

using std::vector;

namespace rtx
{
	using namespace render;
	namespace graph
	{

		class RenderTarget
		{
		public:

			void Draw(const Drawable& drawable)const;

			void Draw(const Drawable& drawable, Shader& shader)const;

			void Draw(const vector<Vertex>& vertices, unsigned int vao)const;

			void Draw(const vector<unsigned int>& indices, unsigned int vao)const;

		};
	}
}

#endif // !RENDERTARGET_H
