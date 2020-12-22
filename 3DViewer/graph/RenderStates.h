#ifndef RENDERSTATES_H
#define RENDERSTATES_H

#include"Drawable.h"

#include"../render/Shader.h"
#include"../render/Texture.h"
#include"Drawable.h"
#include<memory>

using rtx::graph::Drawable;
using std::shared_ptr;
using rtx::render::Shader;
using rtx::render::Texture;
namespace rtx
{
	namespace graph
	{
		class RenderStates
		{
		public:

			RenderStates();

			RenderStates(Shader& theShader);

			RenderStates(Texture& theTexture);

			Shader* GetShader()
			{
				return shader;
			}

			Texture* GetTexture()
			{
				return texture;
			}

		private:

			Shader* shader;
			Texture* texture;

		};
	}
}

#endif // !RENDERSTATES_H
