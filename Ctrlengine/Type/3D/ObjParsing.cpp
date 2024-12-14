#include "ObjParsing.hpp"

namespace cte {
    void ObjParsing::loadModel(const std::string& path, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices) {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            throw std::runtime_error("Assimp Error: " + std::string(importer.GetErrorString()));
        }

        processNode(scene->mRootNode, scene, vertices, indices);
    }

    void processNode(aiNode* node, const aiScene* scene, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices) {
        for (unsigned int i = 0; i < node->mNumMeshes; i++) {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            for (unsigned int j = 0; j < mesh->mNumVertices; j++) {
                Vertex vertex;
                vertex.pos = glm::vec3(mesh->mVertices[j].x, mesh->mVertices[j].y, mesh->mVertices[j].z);
                vertex.normal = glm::vec3(mesh->mNormals[j].x, mesh->mNormals[j].y, mesh->mNormals[j].z);
                if (mesh->mTextureCoords[0]) {
                    vertex.texCoord = glm::vec2(mesh->mTextureCoords[0][j].x, mesh->mTextureCoords[0][j].y);
                }
                else {
                    vertex.texCoord = glm::vec2(0.0f, 0.0f); // 或者根据需要进行处理
                }
                vertices.push_back(vertex);
            }
            for (unsigned int j = 0; j < mesh->mNumFaces; j++) {
                aiFace face = mesh->mFaces[j];
                for (unsigned int k = 0; k < face.mNumIndices; k++) {
                    indices.push_back(face.mIndices[k]);
                }
            }
        }
        for (unsigned int i = 0; i < node->mNumChildren; i++) {
            processNode(node->mChildren[i], scene, vertices, indices);
        }
    }
}