#ifndef DRAWABLE_H
#define DRAWABLE_H

#include"../render/Transform.h"
#include"../render/Shader.h"
namespace rtx
{

	using render::Transform;
	using render::Shader;

	namespace graph
	{

		class RenderTarget;

		class RenderStates;

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

			friend class RenderStates;

			virtual void Draw(const RenderTarget& target, RenderStates states)const = 0;

		};
	}
}

#endif // !DRAWABLE_H
