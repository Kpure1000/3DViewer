#ifndef SPHEREMESH_H
#define SPHEREMESH_H

#include"Mesh.h"

namespace rtx
{
	namespace graph
	{
		class SphereMesh : public Mesh
		{

		public:

			SphereMesh()
				:m_lerpNum(50)
			{
				MeshInit();
			}

			~SphereMesh()
			{
				glDeleteVertexArrays(1, &VAO);
				glDeleteBuffers(1, &VBO);
			}

		private:

			virtual void MeshInit()
			{
				int latitu = m_lerpNum, longitu = m_lerpNum;

				float rz1, rz2, rxy1, rxy2;
				Vertex va, vb, vc, vd;
				glm::vec3 normal;
				for (size_t i = 0; i < longitu; i++)
				{
					for (size_t j = 0; j < latitu; j++)
					{
						rz1 = (Pi * j / latitu);
						rz2 = (Pi * (j + 1) / latitu);
						rxy1 = 2 * Pi * i / longitu;
						rxy2 = 2 * Pi * (i + 1) / longitu;
						va.position = { sin(rz1) * cos(rxy1), sin(rz1) * sin(rxy1), cos(rz1) };
						vb.position = { sin(rz2) * cos(rxy1), sin(rz2) * sin(rxy1), cos(rz2) };
						vc.position = { sin(rz2) * cos(rxy2), sin(rz2) * sin(rxy2), cos(rz2) };
						vd.position = { sin(rz1) * cos(rxy2), sin(rz1) * sin(rxy2), cos(rz1) };

						normal = glm::normalize(glm::cross(vd.position - vb.position, va.position - vc.position));
						va.normal = vb.normal = vc.normal = vd.normal = normal;

						va.texCoords.x = (float)i / longitu;
						va.texCoords.y = (float)j / longitu;

						vb.texCoords.x = (float)i / longitu;
						vb.texCoords.y = (float)(j + 1) / longitu;

						vc.texCoords.x = (float)(i + 1) / longitu;
						vc.texCoords.y = (float)(j + 1) / longitu;

						vd.texCoords.x = (float)(i + 1) / longitu;
						vd.texCoords.y = (float)j / longitu;

						vertices.push_back(va);
						vertices.push_back(vb);
						vertices.push_back(vd);
						vertices.push_back(vb);
						vertices.push_back(vc);
						vertices.push_back(vd);

					}
				}

				glGenVertexArrays(1, &VAO);
				glGenBuffers(1, &VBO);

				glBindVertexArray(VAO);
				glBindBuffer(GL_ARRAY_BUFFER, VBO);

				glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

				//  position
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
				glEnableVertexAttribArray(0);
				//  normal
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
				glEnableVertexAttribArray(1);
				//  texcoords
				glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
				glEnableVertexAttribArray(2);

				glBindVertexArray(0);
			}

			virtual void Draw(const RenderTarget& target, RenderStates&& states)const
			{
				if (m_isActived)
					target.Draw(vertices, VAO);
			}

			int m_lerpNum;

		};
	}
}

#endif // !SPHEREMESH_H
