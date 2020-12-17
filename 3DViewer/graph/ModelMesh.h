#ifndef MODELMESH_H
#define MODELMESH_H

#include"Mesh.h"
#include"../render/Shader.h"

#include<iostream>


namespace rtx
{

    using namespace render;

	namespace graph
	{
        class ModelMesh : public Mesh
        {
        public:
            /*  º¯Êý   */
            ModelMesh()                
            {}

            ModelMesh(vector<Vertex> Vertices, vector<unsigned int> Indices, vector<MeshTex> Textures)
                : Mesh(Vertices, Indices, Textures)
            {
                MeshInit();
                printf("Model Vertices: %zd, Indices: %zd, Textures: %zd.\n", vertices.size(), indices.size(), textures.size());
            }

            ~ModelMesh()
            {
                glDeleteVertexArrays(1, &VAO);
                glDeleteBuffers(1, &VBO);
            }

        private:

            virtual void MeshInit()
            {
                glGenVertexArrays(1, &VAO);
                glGenBuffers(1, &VBO);
                glGenBuffers(1, &EBO);

                glBindVertexArray(VAO);
                glBindBuffer(GL_ARRAY_BUFFER, VBO);

                glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

                //  position
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
                glEnableVertexAttribArray(0);
                //  normal
                glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
                glEnableVertexAttribArray(1);
                //  texcoords
                glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
                glEnableVertexAttribArray(2);
                //  color
               /* glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
                glEnableVertexAttribArray(3);*/

                glBindVertexArray(0);
            }

            virtual void Draw(const RenderTarget& target, RenderStates states)const
            {
                if (m_isActived)
                {
                    if (states.shader != nullptr)
                    {
                        unsigned int diffuseNr = 1;
                        unsigned int specularNr = 1;
                        unsigned int normalNr = 1;
                        unsigned int heightNr = 1;
                        for (auto item = textures.begin(); item != textures.end(); item++)
                        {
                            item->texture.Bind();
                            std::string number;
                            std::string name = item->type;
                            if (name == "_DiffuseTex")
                            {
                                number = std::to_string(diffuseNr++);
                            }
                            else if (name == "_SpecularTex")
                            {
                                number = std::to_string(specularNr++);
                            }
                            else if (name == "texture_normal")
                            {
                                number = std::to_string(normalNr++);
                            }
                            else if (name == "texture_height")
                            {
                                number = std::to_string(heightNr++);
                            }
                            states.shader->SetSampler2D("_metarial." + name + number, item->texture);
                        }
                        //target.Draw(indices, VAO);
                        target.Draw(vertices, VAO);
                    }
                }
            }

        };
	}
}
#endif // !MODELMESH_H
