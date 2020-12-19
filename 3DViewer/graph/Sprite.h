#ifndef SPRITE_H
#define SPRITE_H

#include"RenderStates.h"
#include"RenderTarget.h"
#include"Drawable.h"

namespace rtx
{
	namespace graph
	{
		class Sprite : Drawable
		{
		public:

			Sprite() :VAO(0), VBO(0), EBO(0)
			{
                Vertex a;
                a.position = glm::vec3(0.0f, 0.0f, 0.0f);
                a.normal = glm::vec3(0.0f, 0.0f, 1.0f);
                a.texCoords = glm::vec2(0.0f, 0.0f);
                Vertex b;
                b.position = glm::vec3(0.0f, 1.0f, 0.0f);
                b.normal = glm::vec3(0.0f, 0.0f, 1.0f);
                b.texCoords = glm::vec2(0.0f, 1.0f);
                Vertex c;
                c.position = glm::vec3(1.0f, 1.0f, 0.0f);
                c.normal = glm::vec3(0.0f, 0.0f, 1.0f);
                c.texCoords = glm::vec2(1.0f, 1.0f);
                Vertex d;
                d.position = glm::vec3(1.0f, 0.0f, 0.0f);
                d.normal = glm::vec3(0.0f, 0.0f, 1.0f);
                d.texCoords = glm::vec2(1.0f, 0.0f);
                vertices.push_back(a);
                vertices.push_back(b);
                vertices.push_back(c);
                vertices.push_back(d);

				int indi[] = {
		            0,1,2,
		            2,3,0
				};
                indices.reserve(6);
                indices.assign(indi, indi + 6);

				SpriteInit();
			}

            Sprite(const std::string& filePath) :VAO(0), VBO(0), EBO(0)
            {
                m_texture.LoadFromFile(filePath);
                Vertex a;
                a.position = glm::vec3(0.0f, 0.0f, 0.0f);
                a.normal = glm::vec3(0.0f, 0.0f, 1.0f);
                a.texCoords = glm::vec2(0.0f, 0.0f);
                Vertex b;
                b.position = glm::vec3(0.0f, 1.0f, 0.0f);
                b.normal = glm::vec3(0.0f, 0.0f, 1.0f);
                b.texCoords = glm::vec2(0.0f, 1.0f);
                Vertex c;
                c.position = glm::vec3(1.0f, 1.0f, 0.0f);
                c.normal = glm::vec3(0.0f, 0.0f, 1.0f);
                c.texCoords = glm::vec2(1.0f, 1.0f);
                Vertex d;
                d.position = glm::vec3(1.0f, 0.0f, 0.0f);
                d.normal = glm::vec3(0.0f, 0.0f, 1.0f);
                d.texCoords = glm::vec2(1.0f, 0.0f);
                vertices.push_back(a);
                vertices.push_back(b);
                vertices.push_back(c);
                vertices.push_back(d);

                int indi[] = {
                    0,1,2,
                    2,3,0
                };
                indices.reserve(6);
                indices.assign(indi, indi + 6);

                SpriteInit();
            }

            void SetTexture(const std::string filePath)
            {
                m_texture.LoadFromFile(filePath);
            }

            void SetTexture(const Texture& texture)
            {
                m_texture = texture;
            }

		private:

			void SpriteInit()
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

			}


            /**************************************************/

            friend class RenderTarget;

            unsigned int VAO, VBO, EBO;

            vector<Vertex> vertices;

            vector<unsigned int> indices;

            Texture m_texture;

		};
	}
}
#endif // !SPRITE_H
