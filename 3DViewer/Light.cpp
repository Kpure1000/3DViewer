#include"render/Light.h"
#include<string>
using std::string;
namespace rtx
{
	namespace render
	{
		Transform Light::GetTransform()const
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

		Transform& Light::GetTransform()
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

		void Light::LightInShader(Shader& shader, int index)const
		{
			string lightStr = "_lights[" + std::to_string(index) + "]";
			shader.SetInt(lightStr + ".lightType", static_cast<int>(m_lightType));

			shader.SetVector3(lightStr + ".position", GetTransform().GetPosition());

			shader.SetRGB(lightStr + ".ambient", util::Color(0x0f0f0f));
			shader.SetRGB(lightStr + ".diffuse", m_color);
			shader.SetRGB(lightStr + ".specular", m_color);

			shader.SetFloat(lightStr + ".constant", m_attenuation[0]);
			shader.SetFloat(lightStr + ".linear", m_attenuation[1]);
			shader.SetFloat(lightStr + ".quadratic", m_attenuation[2]);

			shader.SetVector3(lightStr + ".direction", m_spotDirection);
			shader.SetFloat(lightStr + ".innerCutOff", m_innerCutOff);
			shader.SetFloat(lightStr + ".outerCutOff", m_outerCutOff);
		}
	}
}