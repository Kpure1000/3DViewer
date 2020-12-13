#ifndef VERTEX_H
#define VERTEX_H
#include"../util/Color.h"

namespace rtx
{

	namespace graph
	{

		struct Vertex
		{
			glm::vec3 position;
			glm::vec3 normal;
			glm::vec2 texCoords;

			//  attatch:
			
			glm::vec3 color;
		};

	}
}
#endif // !VERTEX_H

