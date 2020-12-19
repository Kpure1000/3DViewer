#ifndef MODEL_H
#define MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include"ModelMesh.h"
#include<map>

namespace rtx
{
	namespace graph
	{

        /// <summary>
        /// Model class
        /// </summary>
        class Model : public Drawable
        {
        public:
            /*  º¯Êý   */
            Model(std::string path, bool gamma = false)
                :gammaCorrection(gamma)
            {
                loadModel(path);
#ifdef _DEBUG
                printf("Model Load success: %zd models.\n", meshes.size());
#endif
            }

        private:

            virtual void Draw(const RenderTarget& target, RenderStates states)const
            {
                for (size_t i = 0; i < meshes.size(); i++)
                {
                    target.Draw(meshes[i], *states.shader);
                }
            }

            vector<ModelMesh> meshes;
            std::map<std::string, MeshTex> texturesLoadPool; 
            vector<MeshTex> textures_loaded;

            std::string directory;
            bool gammaCorrection;
            
            /// <summary>
            /// Load model from file
            /// </summary>
            void loadModel(const std::string& path);
            
            /// <summary>
            /// Process all the Node in Model dir
            /// </summary>
            void processNode(aiNode* node, const aiScene* scene);

            /// <summary>
            /// Process all the Mesh in Model dir
            /// </summary>
            ModelMesh processMesh(aiMesh* mesh, const aiScene* scene);
            
            /// <summary>
            /// Load Texture(may material in the future) from file in the same direction
            /// </summary>
            vector<MeshTex> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
        };
	}
}
#endif // !MODEL_H
