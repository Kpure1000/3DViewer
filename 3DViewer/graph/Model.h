#ifndef MODEL_H
#define MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include"ModelMesh.h"

namespace rtx
{
	namespace graph
	{
        class Model : public Drawable
        {
        public:
            /*  º¯Êý   */
            Model(std::string path)
            {
                loadModel(path);
                printf("Model Load success: %zd models.\n", meshes.size());
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

            std::string directory;
            
            void loadModel(std::string path);
            
            void processNode(aiNode* node, const aiScene* scene);

            ModelMesh processMesh(aiMesh* mesh, const aiScene* scene);
            
            vector<MeshTex> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
        };
	}
}
#endif // !MODEL_H
