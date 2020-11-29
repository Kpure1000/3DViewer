#include"render/Texture.h"

namespace rtx
{
	namespace render
	{
		int Texture::currentTextureIndex = 0;
		const int Texture::MaxTextureIndices = GL_TEXTURE15 - GL_TEXTURE0;
		std::map<unsigned int, int> Texture::texture_indices;

		Texture::Texture() :m_ID(-1)
		{
			//  TODO: if numbers over Max, cancel?
			if (currentTextureIndex < MaxTextureIndices)
			{
				glGenTextures(1, &m_ID);
				texture_indices[m_ID] = GL_TEXTURE0 + currentTextureIndex++;
				glBindTexture(GL_TEXTURE_2D, m_ID);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			}
			else
			{
				std::cerr << "Textures out of range!\n";
			}
		}

		Texture::~Texture()
		{
			//  TODO: need to release bind?
		}

		void Texture::Use()const
		{
			if (texture_indices.find(m_ID) != texture_indices.end())
			{
				glActiveTexture(texture_indices[m_ID]);
				glBindTexture(GL_TEXTURE_2D, m_ID);
				image.Use();
			}
		}

		int Texture::GetIndex()const
		{
			return texture_indices[m_ID] - GL_TEXTURE0;
		}

		unsigned int Texture::GetID()const
		{
			return m_ID;
		}

		void Texture::LoadFromFile(const std::string& path)
		{
			image.LoadFromFile(path.c_str());
		}

		void Texture::LoadFromMemory(int w, int h, int ch, unsigned char* data)
		{
			image.LoadFromMemory(w, h, ch, data);
		}
	}
}