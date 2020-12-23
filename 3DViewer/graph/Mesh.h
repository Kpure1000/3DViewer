#ifndef MESH_H
#define MESH_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<vector>

#include"Vertex.h"
#include"../render/Texture.h"
#include"../render/Shader.h"

#include"Drawable.h"
#include"RenderTarget.h"
#include"RenderStates.h"

using std::vector;
using namespace rtx::render;

namespace rtx
{
	namespace graph
	{
		class Mesh : public Drawable
		{
		public:

            Mesh()
                :VAO(0), VBO(0), EBO(0)
            {}

            Mesh(vector<Vertex> Vertices, vector<unsigned int> Indices, vector<MeshTex> Textures)
                :VAO(0), VBO(0), EBO(0), vertices(Vertices), indices(Indices), textures(Textures)
            {}

        protected:

            virtual void MeshInit() = 0;

            virtual void Draw(const RenderTarget& target, RenderStates&& states)const = 0;

            /**************************************************/

            friend class RenderTarget;

            unsigned int VAO, VBO, EBO;

            vector<Vertex> vertices;

            vector<unsigned int> indices;
            
            vector<MeshTex> textures;

		};
	}
}

#endif // !MESH_H
