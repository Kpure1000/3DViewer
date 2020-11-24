#ifndef VERTEX_H
#define VERTEX_H
#include"../util/Color.h"

namespace rtx
{

	namespace graph
	{

		class Vertex
		{
		public:

			Vertex() {}

			Vertex(float x, float y, float z) :position(x, y, z) {}

			Vertex(glm::vec3 pos) :position(pos) {}

			Vertex(glm::vec3 pos, util::Color col) :position(pos),color(col) {}

			Vertex(glm::vec3 pos, util::Color col, glm::vec2 tex) :position(pos), color(col), texCoords(tex) {}

			float* GetVertics()
			{
				for (size_t i = 0; i < 3; i++)
				{
					vertics[i] = position[i];
				}
				return vertics;
			}

			glm::vec3 position;

			util::Color color;

			glm::vec2 texCoords;

		private:

			float vertics[3] = { 0,0,0 };

		};

	}
}
#endif // !VERTEX_H

