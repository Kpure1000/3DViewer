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

        /// <summary>
        /// The mesh of a model, which may include more than one model mesh. 
        /// So this might be contained in a vector or array. 
        /// The Material will be added.
        /// </summary>
        class ModelMesh : public Mesh
        {
        public:
            /*  º¯Êý   */
            ModelMesh()                
            {}

            /// <summary>
            /// Construct a Model Mesh (Used in Model function: 'processMesh')
            /// </summary>
            /// <param name="Vertices"></param>
            /// <param name="Indices"></param>
            /// <param name="Textures"></param>
            ModelMesh(vector<Vertex> Vertices, vector<unsigned int> Indices, vector<MeshTex> Textures)
                : Mesh(Vertices, Indices, Textures)
            {
                MeshInit();
#ifdef _DEBUG
                printf("Model Vertices: %zd, Indices: %zd, Textures: %zd.\n", vertices.size(), indices.size(), textures.size());
#endif
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
                // vertex tangent
                glEnableVertexAttribArray(3);
                glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
                // vertex bitangent
                glEnableVertexAttribArray(4);
                glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));

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
                        for (size_t i = 0; i < textures.size(); i++)
                        {
                            std::string number;
                            std::string name = textures[i].type;
                            if (name == "texture_diffuse")
                                number = std::to_string(diffuseNr++);
                            else if (name == "texture_specular")
                                number = std::to_string(specularNr++); // transfer unsigned int to stream
                            else if (name == "texture_normal")
                                number = std::to_string(normalNr++); // transfer unsigned int to stream
                            else if (name == "texture_height")
                                number = std::to_string(heightNr++); // transfer unsigned int to stream

                            textures[i].texture.ReBind((int)i);
                            states.shader->Use();
                            states.shader->SetSampler2D("_material" + name + number, (int)i);
                        }
                        target.Draw(vertices, VAO);
                    }
                }
            }

        };
	}
}
#endif // !MODELMESH_H
