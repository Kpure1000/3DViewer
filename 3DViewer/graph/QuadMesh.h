#ifndef QUADMESH_H
#define QUADMESH_H

#include "Mesh.h"

namespace rtx
{
	namespace graph
	{
		class QuadMesh : public Mesh
		{
		public:
			QuadMesh()
			{
				MeshInit();
			}

			// Í¨¹ý Mesh ¼Ì³Ð
			virtual void MeshInit() override
			{
				//  2---3
				//  | / |
				//  1---4

				Vertex va; va.position = glm::vec3(-0.5, 0.5, 0.0f); //1
				Vertex vb; vb.position = glm::vec3(-0.5, -0.5, 0.0f);//2
				Vertex vc; vc.position = glm::vec3(0.5, -0.5, 0.0f);//3

				Vertex vd; vd.position = glm::vec3(-0.5, 0.5, 0.0f);//1
				Vertex ve; ve.position = glm::vec3(0.5, -0.5, 0.0f);//3
				Vertex vf; vf.position = glm::vec3(0.5, 0.5, 0.0f);//4

				va.normal = vb.normal
					= vc.normal = vd.normal
					= ve.normal = vf.normal
					= glm::vec3(0.0f, 0.0f, 1.0f);

				va.texCoords = glm::vec2(0, 1);
				vb.texCoords = glm::vec2(0, 0);
				vc.texCoords = glm::vec2(1, 0);
				vd.texCoords = glm::vec2(0, 1);
				ve.texCoords = glm::vec2(1, 0);
				vf.texCoords = glm::vec2(1, 1);
				
				glm::vec3 edge1, edge2;
				glm::vec2 deltaUV1, deltaUV2;
				glm::vec3 tangent1, bitangent1;

				edge1 = vb.position - va.position;
				edge2 = vc.position - va.position;
				deltaUV1 = vb.texCoords - va.texCoords;
				deltaUV2 = vc.texCoords - va.texCoords;
				float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);
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

			virtual void Draw(const RenderTarget& target, RenderStates&& states) const override
			{
				if (m_isActived)
					target.Draw(vertices, VAO);
			}
		};
	}
}

#endif // !QUADMESH_H
