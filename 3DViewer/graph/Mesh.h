#ifndef MESH_H
#define MESH_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<vector>

#include"Vertex.h"
#include"../render/Texture.h"

#include"Drawable.h"
#include"RenderTarget.h"

using std::vector;
using namespace rtx::render;

namespace rtx
{
	namespace graph
	{
		class Mesh : public Drawable
		{
		public:

            Mesh() :verticesOffset(0) {}

        protected:

            virtual void MeshInit() = 0;

            virtual void Draw(RenderTarget target)const = 0;

            friend class RenderTarget;

            unsigned int VAO, VBO, EBO;

            vector<Vertex> vertices;

            int verticesOffset;

            vector<unsigned int> indices;
            
            vector<Texture> textures;

		};
	}
}

#endif // !MESH_H
