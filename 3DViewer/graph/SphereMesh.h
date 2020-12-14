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
				:radius(1.0f), lerpNum(100)
			{
				int latitu = lerpNum, longitu = lerpNum;

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
						va.position = { radius * sin(rz1) * cos(rxy1),radius * sin(rz1) * sin(rxy1),radius * cos(rz1) };
						vb.position = { radius * sin(rz2) * cos(rxy1),radius * sin(rz2) * sin(rxy1),radius * cos(rz2) };
						vc.position = { radius * sin(rz2) * cos(rxy2),radius * sin(rz2) * sin(rxy2),radius * cos(rz2) };
						vd.position = { radius * sin(rz1) * cos(rxy2),radius * sin(rz1) * sin(rxy2),radius * cos(rz1) };

						normal = glm::normalize(glm::cross(vd.position - vb.position, va.position - vc.position));
						va.normal = vb.normal = vc.normal = vd.normal = normal;

						vertices.push_back(va);
						vertices.push_back(vb);
						vertices.push_back(vd);
						vertices.push_back(vb);
						vertices.push_back(vc);
						vertices.push_back(vd);

					}
				}

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
				glGenVertexArrays(1, &VAO);
				glGenBuffers(1, &VBO);

				glBindVertexArray(VAO);
				glBindBuffer(GL_ARRAY_BUFFER, VBO);

				glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

				//  position
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
				glEnableVertexAttribArray(0);
				verticesOffset += 3;
				//  normal
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
				glEnableVertexAttribArray(1);
				verticesOffset += 3;
				//  texcoords
				glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
				glEnableVertexAttribArray(2);
				verticesOffset += 2;
				//  color
				glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
				glEnableVertexAttribArray(3);
				verticesOffset += 3;

				//glBindVertexArray(0);
			}

			virtual void Draw(RenderTarget target)const
			{
				if (m_isActived)
					target.Draw(vertices, verticesOffset, VAO);
			}

			float radius;

			int lerpNum;

		};
	}
}

#endif // !SPHEREMESH_H
