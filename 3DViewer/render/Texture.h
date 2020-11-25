#ifndef TEXTURE_H
#define TEXTURE_H

#include<glad/glad.h>

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<map>

#include"Image.h"

namespace rtx
{
	namespace render
	{
		class Texture
		{
		public:

			Texture();

			~Texture();

			void LoadFromFile(const std::string& path);

			void LoadFromMemory(int w, int h, int ch, unsigned char* data);

			void Use()const;

			int GetIndex()const
			{
				return texture_indices[m_ID] - GL_TEXTURE0;
			}

			unsigned int GetID()const
			{
				return m_ID;
			}

		private:

			unsigned int m_ID;

			Image image;

			/// <summary>
			/// <ID,GL_TEXTUREn>
			/// </summary>
			static std::map<unsigned int, int>texture_indices;

			static int currentTextureIndex;
			
			const static int MaxTextureIndices;

		};

	}
}
#endif // !TEXTURE_H
