#pragma once
#include "../../Vulkan/CteVulkan.hpp"
#include "objModel.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vulkan/vulkan.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

namespace cte {
	class CteObjModel
	{
	public:
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
		std::vector<Texture> textures;
		void loadObjModel(const std::string& filePath);
        void processNode(aiNode* node, const aiScene* scene);
        void processMesh(aiMesh* mesh, const aiScene* scene);
        void loadTexture(aiMaterial* mat, aiTextureType type, std::string typeName);
	};
}
