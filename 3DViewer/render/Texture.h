#ifndef TEXTURE_H
#define TEXTURE_H

#include<glad/glad.h>

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>

#include"Image.h"

namespace rtx
{
	namespace render
	{
		class Texture
		{
		public:

			Texture();

			Texture(const std::string& path);

			~Texture();

			void LoadFromFile(const std::string& path);

			void LoadFromMemory(int w, int h, int ch, unsigned char* data);

			void Use()const
			{
				glActiveTexture(m_ID);
				glBindTexture(GL_TEXTURE_2D, m_ID);
				image.Use();
			}

			unsigned int GetID()const
			{
				return m_ID;
			}

		private:

			unsigned int m_ID;

			Image image;

		};

	}
}
#endif // !TEXTURE_H
