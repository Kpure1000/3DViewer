#ifndef LIGHT_H
#define LIGHT_H
#include"../graph/Mesh.h"
#include<memory>
#include<array>
using std::shared_ptr;
using std::make_shared;
using std::array;
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
				Directional = 0,
				Point = 1,
				Spot = 2
			};

			Light()
				:m_mesh(nullptr), m_color(0xffffff), m_lightType(LightType::Point)
			{
				m_color = Color();
				m_innerCutOff = 0.0f;
				m_outerCutOff = 0.0f;
				m_spotDirection = glm::vec3(1.0f);
				m_attenuation[0] = 1.0f;
				m_attenuation[1] = 0.07f;
				m_attenuation[2] = 0.017f;
			}

			Light(const shared_ptr<Mesh>& mesh, const LightType& type)
				:m_mesh(mesh), m_lightType(type)
			{
				m_color = Color();
				m_innerCutOff = 0.0f;
				m_outerCutOff = 0.0f;
				m_spotDirection = glm::vec3(1.0f);
				m_attenuation[0] = 1.0f;
				m_attenuation[1] = 0.07f;
				m_attenuation[2] = 0.017f;
			}

			Light(shared_ptr<Mesh>&& mesh, const LightType& type)
				:m_mesh(mesh), m_lightType(type)
			{
				m_color = Color();
				m_innerCutOff = 0.0f;
				m_outerCutOff = 0.0f;
				m_spotDirection = glm::vec3(1.0f);
				m_attenuation[0] = 1.0f;
				m_attenuation[1] = 0.07f;
				m_attenuation[2] = 0.017f;
			}

			/// <summary>
			/// Get mesh of light
			/// </summary>
			/// <returns></returns>
			inline shared_ptr<Mesh> GetMesh()const
			{
				return m_mesh;
			}

			/// <summary>
			/// Get light position
			/// </summary>
			/// <returns></returns>
			inline glm::vec3 GetPosition()const
			{
				return GetTransform().GetPosition();
			}

			Transform GetTransform()const;

			Transform& GetTransform();

			inline Color GetColor()const
			{
				return m_color;
			}

			inline float GetInnerCutOff()const
			{
				return m_innerCutOff;
			}

			inline float GetOuterCutOff()const
			{
				return m_outerCutOff;
			}

			inline glm::vec3 GetSpotDirection()const
			{
				return m_spotDirection;
			}

			inline LightType GetLightType()const
			{
				return m_lightType;
			}

			/********************************************************/

			/// <summary>
			/// Set light position
			/// </summary>
			/// <param name="position"></param>
			inline void SetPosition(glm::vec3 position)
			{
				m_mesh->GetTransform().SetPosition(position);
			}

			inline void SetColor(const Color& color)
			{
				m_color = color;
			}

			inline void SetColor(Color&& color)
			{
				m_color = std::move(color);
			}

			inline void SetInnerCutOff(float const& inner)
			{
				m_innerCutOff = glm::cos(glm::radians(inner));
			}

			inline void SetOuterCutOff(float const& outer)
			{
				m_outerCutOff = glm::cos(glm::radians(outer));
			}

			inline void SetSpotDirection(glm::vec3 spotDiretion)
			{
				m_spotDirection = spotDiretion;
			}

			inline void SetLightType(LightType lightType)
			{
				m_lightType = lightType;
			}

			/********************************************************/

			/// <summary>
			/// Light to material shader
			/// </summary>
			/// <param name="shader"></param>
			void LightInShader(Shader& shader, int index)const;

		private:

			virtual void Draw(const RenderTarget& target, RenderStates&& states)const
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

			array<float, 3> m_attenuation;

			/// <summary>
			/// Inner cut off (only spot light)
			/// </summary>
			float m_innerCutOff;

			/// <summary>
			/// Outer cut off (only spot light)
			/// </summary>
			float m_outerCutOff;

			/// <summary>
			/// Direction of spot light (only spot light)
			/// </summary>
			glm::vec3 m_spotDirection;

			LightType m_lightType;

		};
	}
}
#endif // !LIGHT_H
