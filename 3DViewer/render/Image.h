#ifndef IMAGE_H
#define IMAGE_H

#include<stb/stb_image.h>
#include<stb/stb_image_write.h>
#include<vector>
#include<functional>
using std::vector;
using std::function;

namespace rtx
{
	namespace render
	{

		class Image
		{
		public:

			Image()
				:width(0), height(0), channel(0),
				loadMode(LoadMode::NONE)
			{}

			/// <summary>
			/// Load image from memory
			/// </summary>
			/// <param name="w">Width</param>
			/// <param name="h">Heigt</param>
			/// <param name="ch">Channel</param>
			/// <param name="data">Image data</param>
			void LoadFromMemory(const int& w, const int& h, const int& ch, unsigned char* data)
			{
				loadMode = LoadMode::LOAD_MEMORY;
				this->width = w;
				this->height = h;
				this->channel = ch;

				imageData.reserve((size_t)w * (size_t)h * (size_t)ch);
				imageData.assign(data, data + (size_t)w * (size_t)h * (size_t)ch);
				CheckBuffer(imageData.size());
			}

			/// <summary>
			/// Load image from a vector
			/// </summary>
			/// <param name="w">Width</param>
			/// <param name="h">Heigt</param>
			/// <param name="ch">Channel</param>
			/// <param name="data">Image data(in vector)</param>
			void LoadFromMemory(const int& w, const int& h, const int& ch, const vector<unsigned char>& data)
			{
				loadMode = LoadMode::LOAD_MEMORY;
				this->width = w;
				this->height = h;
				this->channel = ch;
				imageData = data;
				CheckBuffer(imageData.size());
			}

			/// <summary>
			/// Load image from file and set weather flip y-axis or not
			/// </summary>
			/// <param name="path"></param>
			/// <param name="isFlip"></param>
			void LoadFromFile(const std::string& path, bool isFlip)
			{
				loadMode = LoadMode::LOAD_FILE;
				stbi_set_flip_vertically_on_load(isFlip);

				auto data = stbi_load(path.c_str(), &width, &height, &channel, 0);
				imageData.reserve((size_t)width * (size_t)height * (size_t)channel);
				imageData.assign(data, data + (size_t)width * (size_t)height * (size_t)channel);
				stbi_image_free(data);
				CheckBuffer(imageData.size());
			}

			/// <summary>
			/// Load image from file
			/// </summary>
			/// <param name="path"></param>
			void LoadFromFile(const std::string& path)
			{
				LoadFromFile(path, true);
			}

			/// <summary>
			/// Bind current data to Texture Image Cache, 
			/// and generate a 2D mipmap
			/// </summary>
			void Use()const
			{
				if (imageData.size() != 0 && loadMode != LoadMode::NONE)
				{
					if (channel == 3)
					{
						glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData.data());
						glGenerateMipmap(GL_TEXTURE_2D);
					}
					else if (channel == 4)
					{
						glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData.data());
						glGenerateMipmap(GL_TEXTURE_2D);
					}
					else
					{
						std::cerr << "Texture image channel numbers error.\n";
					}
				}
				else
				{
					std::cerr << "Image Buffer is Empty!\n";
				}
			}

			/// <summary>
			/// Deal image data with imageDealCallBack
			/// </summary>
			/// <param name="imageDealCallBack">The dealing method defined by user</param>
			void DealImage(function<void(int, int, int, vector<unsigned char>&)>imageDealCallBack)
			{
				imageDealCallBack(width, height, channel, imageData);
			}

			/// <summary>
			/// Save current data to PNG
			/// </summary>
			/// <param name="path">File path</param>
			void SaveData(const std::string& path)
			{
				if (stbi_write_png(path.c_str(), width, height, channel, imageData.data(), 0) == 0)
				{
					std::cerr << "Save image data error: " << path << std::endl;
				}
			}

		private:

			/// <summary>
			/// Check weather image data with data size
			/// </summary>
			/// <param name="size">Size of data vector</param>
			/// <returns>Size is not zero</returns>
			bool CheckBuffer(size_t size)const
			{
				if (size == 0)
				{
					if (loadMode == LoadMode::LOAD_FILE)
					{
						std::cerr << "Load Image Error: from file.\n";
					}
					else
					{
						std::cerr << "Load Image Error: from other source.\n";
					}
					return false;
				}
				return true;
			}

			int width, height, channel;

			vector<unsigned char> imageData;

			/// <summary>
			/// Load from where
			/// </summary>
			enum class LoadMode
			{
				NONE,
				LOAD_MEMORY,
				LOAD_FILE,
				LOAD_IMAGE
			};

			LoadMode loadMode;
		};

	}
}
#endif // !IMAGE_H
