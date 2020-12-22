#ifndef LIGHT_H
#define LIGHT_H
#include"../graph/Mesh.h"
#include<memory>
using std::shared_ptr;
using std::make_shared;
namespace rtx
{
	using graph::Mesh;
	using graph::RenderTarget;
	using graph::RenderStates;

	namespace render
	{
		class Light : public Drawable
		{
		public:

			enum class LightType
			{
				Directional,
				Point,
				Spot
			};

			Light()
				:m_mesh(nullptr)
			{}

			Light(const shared_ptr<Mesh>& mesh)
				:m_mesh(mesh), m_color(0xffffff), m_lightType(LightType::Point)
			{}

			Light(const shared_ptr<Mesh>& mesh, const glm::vec3& position)
				:m_mesh(mesh), m_color(0xffffff), m_lightType(LightType::Point)
			{
				m_mesh->GetTransform().SetPosition(position);
			}

			Light(const shared_ptr<Mesh>& mesh, const glm::vec3& position, const Color& color)
				:m_mesh(mesh), m_color(color), m_lightType(LightType::Point)
			{
				m_mesh->GetTransform().SetPosition(position);
			}

			Light(shared_ptr<Mesh>&& mesh)
				:m_mesh(mesh), m_color(0xffffff), m_lightType(LightType::Point)
			{}

			Light(shared_ptr<Mesh>&& mesh, const glm::vec3& position)
				:m_mesh(mesh), m_color(0xffffff), m_lightType(LightType::Point)
			{
				m_mesh->GetTransform().SetPosition(position);
			}

			Light(shared_ptr<Mesh>&& mesh, const glm::vec3& position, const Color& color)
				:m_mesh(mesh), m_color(color), m_lightType(LightType::Point)
			{
				m_mesh->GetTransform().SetPosition(position);
			}

			inline LightType GetLightType()const
			{
				return m_lightType;
			}

			inline Color GetColor()const
			{
				return m_color;
			}

			/*inline Color& GetColor()
			{
				return m_color;
			}*/

			Transform& GetTransform()
			{
				if (m_mesh)
				{
					return m_mesh->GetTransform();
				}
				else
				{
					throw std::exception("ERROR: Light: Mesh is null.\n");
				}
			}

			Transform GetTransform()const
			{
				if (m_mesh)
				{
					return static_cast<shared_ptr<const Mesh>>(m_mesh)->GetTransform();
				}
				else
				{
					throw std::exception("ERROR: Light: Mesh is null.\n");
				}
			}

			glm::vec4 GetLightLocation()const
			{
				switch (m_lightType)
				{
				case LightType::Directional:
					return glm::vec4(GetTransform().GetPosition(), 0.1f);
					break;
				case LightType::Point:
					return glm::vec4(GetTransform().GetPosition(), 1.0f);
					break;
				case LightType::Spot:
					return glm::vec4(GetTransform().GetPosition(), 1.0f);
					break;
				default:
					return glm::vec4(GetTransform().GetPosition(), 1.0f);
					break;
				}
			}

			inline void SetLightType(LightType lightType)
			{
				m_lightType = lightType;
			}

			inline void SetColor(const Color& color)
			{
				m_color = color;
			}

			inline void SetColor(Color&& color)
			{
				m_color = std::move(color);
			}

		private:

			virtual void Draw(const RenderTarget& target, RenderStates states)const
			{
				target.Draw((*m_mesh));
			}

			/// <summary>
			/// Render mesh
			/// </summary>
			shared_ptr<Mesh> m_mesh;

			/// <summary>
			/// Light emission color
			/// </summary>
			Color m_color;

			LightType m_lightType;

		};
	}
}
#endif // !LIGHT_H
