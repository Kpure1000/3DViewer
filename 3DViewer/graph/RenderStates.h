#ifndef RENDERSTATES_H
#define RENDERSTATES_H

#include"Drawable.h"

#include"../render/Shader.h"
#include"../render/Texture.h"

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

			shared_ptr<const Shader> shader;
			shared_ptr<const Texture> texture;

		};
	}
}

#endif // !RENDERSTATES_H
