#ifndef DRAWABLE_H
#define DRAWABLE_H

#include"../render/Transform.h"

namespace rtx
{

	using render::Transform;

	namespace graph
	{

		class RenderTarget;

		class Drawable
		{

		public:

			Drawable() : m_isActived(true) {}

			inline Transform& GetTransform()
			{
				return m_trans;
			}

			inline Transform GetTransform()const
			{
				return m_trans;
			}

			inline void SetActive(bool active) { m_isActived = active; }

			inline bool isActive()const { return m_isActived; }

		protected:

			inline glm::mat4 GetTransMat()
			{
				return m_trans.GetTransMat();
			}

			bool m_isActived;

			Transform m_trans;

		private:

			friend class RenderTarget;

			virtual void Draw(RenderTarget target)const = 0;

		};
	}
}

#endif // !DRAWABLE_H
