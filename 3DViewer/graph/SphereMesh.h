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
				Vertex va, vb, vc, vd, ve, vf;
				glm::vec3 normal;
				glm::vec3 edge1, edge2;
				glm::vec2 deltaUV1, deltaUV2;
				glm::vec3 tangent1, bitangent1;
				float f;

				for (size_t i = 0; i < longitu; i++)
				{
					for (size_t j = 0; j < latitu; j++)
					{
						rz1 = (Pi * j / latitu);
						rz2 = (Pi * (j + 1) / latitu);
						rxy1 = 2 * Pi * i / longitu;
						rxy2 = 2 * Pi * (i + 1) / longitu;

						va.position = { sin(rz2) * cos(rxy1), sin(rz2) * sin(rxy1), cos(rz2) }; //1
						vb.position = { sin(rz1) * cos(rxy1), sin(rz1) * sin(rxy1), cos(rz1) };//2
						vc.position = { sin(rz1) * cos(rxy2), sin(rz1) * sin(rxy2), cos(rz1) };//3
						vd.position = { sin(rz2) * cos(rxy1), sin(rz2) * sin(rxy1), cos(rz2) };//1
						ve.position = { sin(rz1) * cos(rxy2), sin(rz1) * sin(rxy2), cos(rz1) };//3
						vf.position = { sin(rz2) * cos(rxy2), sin(rz2) * sin(rxy2), cos(rz2) };//4

						normal = glm::normalize(glm::cross(va.position - vb.position, vc.position - vb.position));
						va.normal = vb.normal = vc.normal = vd.normal = ve.normal = vf.normal = normal;

						va.texCoords.x = (float)i / longitu;
						va.texCoords.y = (float)(j + 1) / latitu;

						vb.texCoords.x = (float)i / longitu;
						vb.texCoords.y = (float)j / latitu;

						vc.texCoords.x = (float)(i + 1) / longitu;
						vc.texCoords.y = (float)j / latitu;

						vd.texCoords.x = (float)i / longitu;
						vd.texCoords.y = (float)(j + 1) / latitu;

						ve.texCoords.x = (float)(i + 1) / longitu;
						ve.texCoords.y = (float)(j + 1) / latitu;
						
						vf.texCoords.x = (float)(i + 1) / longitu;
						vf.texCoords.y = (float)j / latitu;

						edge1 = vb.position - va.position;
						edge2 = vc.position - va.position;
						deltaUV1 = vb.texCoords - va.texCoords;
						deltaUV2 = vc.texCoords - va.texCoords;
						f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);
						tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
						tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
						tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
						tangent1 = glm::normalize(tangent1);
						bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
						bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
						bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
						bitangent1 = glm::normalize(bitangent1);
						va.tangent = vb.tangent = vc.tangent = tangent1;
						va.bitangent = vb.bitangent = vc.bitangent = bitangent1;
						vertices.push_back(va);
						vertices.push_back(vb);
						vertices.push_back(vc);

						edge1 = ve.position - vd.position;
						edge2 = vf.position - vd.position;
						deltaUV1 = ve.texCoords - vd.texCoords;
						deltaUV2 = vf.texCoords - vd.texCoords;
						f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);
						tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
						tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
						tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
						tangent1 = glm::normalize(tangent1);
						bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
						bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
						bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
						bitangent1 = glm::normalize(bitangent1);
						vd.tangent = ve.tangent = vf.tangent = tangent1;
						vd.bitangent = ve.bitangent = vf.bitangent = bitangent1;
						vertices.push_back(vd);
						vertices.push_back(ve);
						vertices.push_back(vf);

					}
				}

				glGenVertexArrays(1, &VAO);
				glBindVertexArray(VAO);

				glGenBuffers(1, &VBO);
				glBindBuffer(GL_ARRAY_BUFFER, VBO);

				glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

				//  position
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
				glEnableVertexAttribArray(0);
				//  normal
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
				glEnableVertexAttribArray(1);
				//  texcoords
				glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
				glEnableVertexAttribArray(2);
				//  tangent
				glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
				glEnableVertexAttribArray(3);
				//  bitangent
				glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));
				glEnableVertexAttribArray(4);

				glGenBuffers(1, &EBO);
				//  bind ebo
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
				//  copy element indices data to memory
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

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
