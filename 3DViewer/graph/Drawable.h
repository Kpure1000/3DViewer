#ifndef DRAWABLE_H
#define DRAWABLE_H

namespace rtx
{


	namespace graph
	{

		class RenderTarget;

		class Drawable
		{

		private:

			friend class RenderTarget;

			virtual void Draw(RenderTarget target)const = 0;

		};
	}
}

#endif // !DRAWABLE_H
