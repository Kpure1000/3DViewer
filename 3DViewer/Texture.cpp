#include"render/Texture.h"

namespace rtx
{
	namespace render
	{
		
		const int Texture::MaxTextureIndices = GL_TEXTURE30 - GL_TEXTURE0;
		

		Texture::Texture() :m_ID(-1)
		{

		}

		Texture::~Texture()
		{
			//  TODO: need to release bind?
		}

		void Texture::LoadFromFile(const std::string& path)
		{
			InitBeforeLoad();
			image.LoadFromFile(path.c_str());
			BindAfterLoad();
		}

		void Texture::LoadFromMemory(int w, int h, int ch, unsigned char* data)
		{
			InitBeforeLoad();
			image.LoadFromMemory(w, h, ch, data);
			BindAfterLoad();
		}

		void Texture::LoadFromImage(const Image& image)
		{
			InitBeforeLoad();
			this->image = image;
			BindAfterLoad();
		}

		void Texture::Bind(const int& index)const
		{
			if (index < MaxTextureIndices)
			{
				glActiveTexture(GL_TEXTURE0 + index);
				glBindTexture(GL_TEXTURE_2D, m_ID);
			}
		}

		void Texture::InitBeforeLoad()
		{
			glGenTextures(1, &m_ID);
			glBindTexture(GL_TEXTURE_2D, m_ID);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			//  Mag filter
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			//  Anisotropic Filtering
			//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY, GL_LINEAR_MIPMAP_LINEAR);
		}

		void Texture::BindAfterLoad()
		{
			image.Use();
		}

	}
}