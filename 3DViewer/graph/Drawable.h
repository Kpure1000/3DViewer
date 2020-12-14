#ifndef DRAWABLE_H
#define DRAWABLE_H

namespace rtx
{


	namespace graph
	{

		class RenderTarget;

		class Drawable
		{

		public:

			Drawable() : m_isActived(true) {}

			void SetActive(bool active) { m_isActived = active; }

			bool isActive()const { return m_isActived; }
		
		protected:
		
			bool m_isActived;
		
		private:

			friend class RenderTarget;

			virtual void Draw(RenderTarget target)const = 0;

		};
	}
}

#endif // !DRAWABLE_H
