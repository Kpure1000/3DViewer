#include"graph/RenderStates.h"

namespace rtx
{
	namespace graph
	{
		RenderStates::RenderStates() : shader(nullptr), texture(nullptr)
		{}

		RenderStates::RenderStates(Shader& theShader) : shader(&theShader), texture(nullptr)
		{
		}

		RenderStates::RenderStates(Texture& theTexture) : shader(nullptr), texture(&theTexture)
		{
		}


	}
}