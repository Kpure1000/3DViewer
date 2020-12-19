#ifndef VERTEX_H
#define VERTEX_H
#include"../util/Color.h"

namespace rtx
{

	namespace graph
	{

		/// <summary>
		/// The vertex struct, used in Mesh and Sprite
		/// </summary>
		struct Vertex
		{
			/// <summary>
			/// Position
			/// </summary>
			glm::vec3 position;

			/// <summary>
			/// Normal
			/// </summary>
			glm::vec3 normal;

			/// <summary>
			/// Texture Coords
			/// </summary>
			glm::vec2 texCoords;

			//  attatch:

			/// <summary>
			/// Tangent
			/// </summary>
			glm::vec3 tangent;
			
			/// <summary>
			/// Bitangent
			/// </summary>
			glm::vec3 bitangent;

			
			[[maybe_unused]]
			/// <summary>
			/// May used for Sprite
			/// </summary>
			glm::vec3 color;
		};

	}
}
#endif // !VERTEX_H

