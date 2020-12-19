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
			/// Load data from image
			/// </summary>
			/// <param name="image"></param>
			void LoadFromImage(const Image& image);

			/// <summary>
			/// Bind current texture
			/// </summary>
			void Bind(const int& index)const;

			void ReBind(const int& index)const;

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

			[[deprecated("This constructor will be deleted")]]
			void SetID(const unsigned int& id)
			{
				m_ID = id;
			}

		private:

			void Init();

			/// <summary>
			/// Texture id
			/// </summary>
			unsigned int m_ID;

			/// <summary>
			/// Data
			/// </summary>
			Image image;

			/// <summary>
			/// Max texture numbers in GL
			/// </summary>
			const static int MaxTextureIndices;

		};

//#define FOREACH_TEXTYPE(TEXTYPE) \
//        TEXTYPE(_DiffuseTex)   \
//        TEXTYPE(_SpecularTex)  
//
//#define GENERATE_ENUM(ENUM) ENUM,
//#define GENERATE_STRING(STRING) #STRING,
//
//		enum class MeshTexType {
//			FOREACH_TEXTYPE(GENERATE_ENUM)
//		};
//
//		static const char* TEXTYPE_STR[] = {
//			FOREACH_TEXTYPE(GENERATE_STRING)
//		};

		/// <summary>
		/// Mesh Texture Type
		/// </summary>
		/*enum class MeshTexType
		{
			_DiffuseTex,
			_SpecularTex
		};*/

		/// <summary>
		/// Mesh Texture
		/// </summary>
		struct MeshTex
		{
			Texture texture;
			//MeshTexType type;

			std::string type;
			std::string path;
		};

	}
}
#endif // !TEXTURE_H
