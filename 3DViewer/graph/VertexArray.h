#ifndef VERTEXARRAY_H
#include"graph/Vertex.h"

#include<vector>

namespace rtx
{
	namespace graph
	{
		class VertexArray
		{
		public:
			VertexArray();

			Vertex& operator[](const int& index)
			{
				return vertices[index];
			}

			Vertex operator[](const int& index)const
			{
				return vertices[index];
			}



		private:

			std::vector<Vertex> vertices;



		};

	}
}
#endif // !VERTEXARRAY_H
