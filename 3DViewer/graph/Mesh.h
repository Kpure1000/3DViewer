#ifndef MESH_H
#define MESH_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<vector>

#include"Vertex.h"
#include"../render/Texture.h"

using std::vector;
using namespace rtx::render;

namespace rtx
{
	namespace graph
	{
		class Mesh
		{
		public:

            Mesh() {}

            Mesh(vector<Vertex> Vertices, vector<unsigned int> Indices, vector<Texture> Textures)
                : vertices(Vertices), indices(Indices), textures(Textures)
			{
                Init();
			}

        private:

			void Init()
			{
                glGenVertexArrays(1, &VAO);
                glGenBuffers(1, &VBO);
                glGenBuffers(1, &EBO);

                glBindVertexArray(VAO);
                glBindBuffer(GL_ARRAY_BUFFER, VBO);

                glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                    &indices[0], GL_STATIC_DRAW);

                //  position
                glEnableVertexAttribArray(0);
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
                //  normal
                glEnableVertexAttribArray(1);
                glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
                //  texcoords
                glEnableVertexAttribArray(2);
                glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

                glEnableVertexAttribArray(3);
                glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

                glBindVertexArray(0);
			}

            unsigned int VAO, VBO, EBO;

            vector<Vertex> vertices;

            vector<unsigned int> indices;
            
            vector<Texture> textures;

		};
	}
}

#endif // !MESH_H
