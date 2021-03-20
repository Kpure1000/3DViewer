#include"graph/Model.h"
#include<stb/stb_image.h>
namespace rtx
{
	namespace graph
	{
		void Model::loadModel(const std::string& path)
		{
			// read file via ASSIMP
			Assimp::Importer importer;
			const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
			// check for errors
			if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
			{
				std::cerr << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
				return;
			}
			// retrieve the directory path of the filepath
			directory = path.substr(0, path.find_last_of('/'));

			// process ASSIMP's root node recursively
			processNode(scene->mRootNode, scene);
		}

		void Model::processNode(aiNode* node, const aiScene* scene)
		{
			// process each mesh located at the current node
			for (unsigned int i = 0; i < node->mNumMeshes; i++)
			{
				// the node object only contains indices to index the actual objects in the scene. 
				// the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
				aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
				meshes.push_back(processMesh(mesh, scene));
			}
			// after we've processed all of the meshes (if any) we then recursively process each of the children nodes
			for (unsigned int i = 0; i < node->mNumChildren; i++)
			{
				processNode(node->mChildren[i], scene);
			}
		}

		ModelMesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
		{
			vector<Vertex> vertices;
			vector<unsigned int> indices;
			vector<MeshTex> textures;

			for (unsigned int i = 0; i < mesh->mNumVertices; i++)
			{
				Vertex vertex;
				// find position, normal
				glm::vec3 vector;
				vector.x = mesh->mVertices[i].x;
				vector.y = mesh->mVertices[i].y;
				vector.z = mesh->mVertices[i].z;
				vertex.position = vector;

				if (mesh->HasNormals())
				{
					vector.x = mesh->mNormals[i].x;
					vector.y = mesh->mNormals[i].y;
					vector.z = mesh->mNormals[i].z;
					vertex.normal = vector;
				}

				if (mesh->mTextureCoords[0]) // 网格是否有纹理坐标？
				{
					glm::vec2 vec;
					// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
					// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
					vec.x = mesh->mTextureCoords[0][i].x;
					vec.y = -mesh->mTextureCoords[0][i].y;
					vertex.texCoords = vec;
					// tangent
					vector.x = mesh->mTangents[i].x;
					vector.y = mesh->mTangents[i].y;
					vector.z = mesh->mTangents[i].z;
					vertex.tangent = vector;
					// bitangent
					vector.x = mesh->mBitangents[i].x;
					vector.y = mesh->mBitangents[i].y;
					vector.z = mesh->mBitangents[i].z;
					vertex.bitangent = vector;
				}
				else
					vertex.texCoords = glm::vec2(0.0f, 0.0f);

				vertices.push_back(vertex);
			}
			// 处理索引
			for (unsigned int i = 0; i < mesh->mNumFaces; i++)
			{
				aiFace face = mesh->mFaces[i];
				// retrieve all indices of the face and store them in the indices vector
				for (unsigned int j = 0; j < face.mNumIndices; j++)
					indices.push_back(face.mIndices[j]);
			}

			// process materials
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

			// 1. diffuse maps
			vector<MeshTex> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
			// 2. specular maps
			// It seems like that Assimp doesn't like specular tex in most format
			// So use aiTextureType_AMBIENT to replace the aiTextureType_SPECULAR
			vector<MeshTex> specularMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_specular");
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
			// 3. normal maps
			std::vector<MeshTex> normalMaps = loadMaterialTextures(material, aiTextureType_NORMALS, "texture_normal");
			textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
			// 4. height maps
			std::vector<MeshTex> heightMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_height");
			textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

			return ModelMesh(vertices, indices, textures);
		}

		/// <summary>
		/// Load Texture(may material in the future) from file in the same direction
		/// </summary>
		/// <param name="mat"></param>
		/// <param name="type"></param>
		/// <param name="typeName"></param>
		/// <returns></returns>
		vector<MeshTex> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
		{
		    vector<MeshTex>textures;
		    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
		    {
		        aiString str;
		        mat->GetTexture(type, i, &str);
		        std::string filename = directory + '/' + str.C_Str();
				std::cout << "Texture: " << filename << ", type: " << typeName << std::endl;
		        //  If path not find in tex pool, it should be loaded
		        MeshTex meshTex;
		        if (texturesLoadPool.find(filename) == texturesLoadPool.end())
		        {
		            meshTex.type = typeName;
		            meshTex.texture.LoadFromFile(filename);
		            meshTex.texture.Bind(i);
		            textures.push_back(meshTex);
		            texturesLoadPool[filename] = meshTex;
		        }
		        else
		        {
		            meshTex = texturesLoadPool[filename];
		            textures.push_back(meshTex);
		        }
		    }
		    return textures;
		}

	}
}