#ifndef DRAWABLE_H
#define DRAWABLE_H

#include"../render/Transform.h"

namespace rtx
{

	namespace graph
	{

		class RenderTarget;

		class Drawable
		{

		public:

			Drawable() : m_isActived(true) {}

			Transform& GetTransform()
			{
				return m_trans;
			}

			Transform GetTransform()const
			{
				return m_trans;
			}

			void SetActive(bool active) { m_isActived = active; }

			bool isActive()const { return m_isActived; }

		protected:

			bool m_isActived;

			Transform m_trans;

		private:

			friend class RenderTarget;

			virtual void Draw(RenderTarget target)const = 0;

		};
	}
}

#endif // !DRAWABLE_H
