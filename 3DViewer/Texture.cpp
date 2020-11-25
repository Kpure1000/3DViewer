#include"render/Texture.h"

namespace rtx
{
	namespace render
	{

		Texture::Texture()
		{
			glGenTextures(1, &m_ID);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}

		Texture::Texture(const std::string& path)
		{
			glGenTextures(1, &m_ID);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			image.LoadFromFile(path.c_str());
		}

		Texture::~Texture()
		{
			//  TODO: need to release bind?
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