#include"graph/Model.h"
#include<stb/stb_image.h>
#include<map>
namespace rtx
{
    namespace graph
    {
        void Model::loadModel(std::string path)
        {
            Assimp::Importer import;
            const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

            if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
            {
                std::cerr << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
                return;
            }
            directory = path.substr(0, path.find_last_of('/'));

            processNode(scene->mRootNode, scene);
        }
        void Model::processNode(aiNode* node, const aiScene* scene)
        {
            // 处理节点所有的网格（如果有的话）
            for (unsigned int i = 0; i < node->mNumMeshes; i++)
            {
                aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
                meshes.push_back(processMesh(mesh, scene));
            }
            // 接下来对它的子节点重复这一过程
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
                // 处理顶点位置、法线和纹理坐标
                glm::vec3 vector;
                vector.x = mesh->mVertices[i].x;
                vector.y = mesh->mVertices[i].y;
                vector.z = mesh->mVertices[i].z;
                vertex.position = vector;

                vector.x = mesh->mNormals[i].x;
                vector.y = mesh->mNormals[i].y;
                vector.z = mesh->mNormals[i].z;
                vertex.normal = vector;

                if (mesh->mTextureCoords[0]) // 网格是否有纹理坐标？
                {
                    glm::vec2 vec;
                    vec.x = mesh->mTextureCoords[0][i].x;
                    vec.y = mesh->mTextureCoords[0][i].y;
                    vertex.texCoords = vec;
                }
                else
                    vertex.texCoords = glm::vec2(0.0f, 0.0f);

                vertices.push_back(vertex);
            }
            // 处理索引
            for (unsigned int i = 0; i < mesh->mNumFaces; i++)
            {
                aiFace face = mesh->mFaces[i];
                for (unsigned int j = 0; j < face.mNumIndices; j++)
                    indices.push_back(face.mIndices[j]);
            }
                // 处理材质
            if (mesh->mMaterialIndex >= 0)
            {
                aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
                vector<MeshTex> diffuseMaps = loadMaterialTextures(material,
                    aiTextureType_DIFFUSE, "texture_diffuse");
                textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
                vector<MeshTex> specularMaps = loadMaterialTextures(material,
                    aiTextureType_SPECULAR, "texture_specular");
                textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
            }

            return ModelMesh(vertices, indices, textures);
        }
        vector<MeshTex> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
        {
            std::map<std::string, bool> texturesLoadPool;
            vector<MeshTex>textures;
            for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
            {
                aiString str;
                mat->GetTexture(type, i, &str);
                std::string filename = str.C_Str();
                filename = directory + '/' + filename;
                if (texturesLoadPool.find(filename) == texturesLoadPool.end())
                {
                    MeshTex meshTexture;
                    meshTexture.texture.LoadFromFile(filename);
                    meshTexture.type = typeName;
                    texturesLoadPool[filename] = true;
                    textures.push_back(meshTexture);
                }
            }
            return textures;
        }
    }
}