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

			/// <summary>
			/// Load Data From File by stbi
			/// </summary>
			/// <param name="path"></param>
			void LoadFromFile(const std::string& path);

			/// <summary>
			/// Load Data From Memory
			/// </summary>
			/// <param name="w"></param>
			/// <param name="h"></param>
			/// <param name="ch"></param>
			/// <param name="data"></param>
			void LoadFromMemory(int w, int h, int ch, unsigned char* data);

			/// <summary>
			/// Bind or Active the Texture
			/// </summary>
			void Use()const;

			/// <summary>
			/// Get index of texture in GL
			/// </summary>
			/// <returns></returns>
			int GetIndex()const;

			/// <summary>
			/// Get id of texture
			/// </summary>
			/// <returns></returns>
			unsigned int GetID()const;

		private:

			/// <summary>
			/// Texture id
			/// </summary>
			unsigned int m_ID;

			/// <summary>
			/// Data
			/// </summary>
			Image image;

			/// <summary>
			/// <ID,GL_TEXTUREn>
			/// </summary>
			static std::map<unsigned int, int>texture_indices;

			/// <summary>
			/// the highest index in GL
			/// </summary>
			static int currentTextureIndex;
			
			/// <summary>
			/// Max texture numbers in GL
			/// </summary>
			const static int MaxTextureIndices;



		};

	}
}
#endif // !TEXTURE_H
