#pragma once
#include "../CteVulkan.hpp"
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>
#include <stdexcept>
struct Vertex {
	glm::vec3 pos;
	glm::vec3 normal;
	glm::vec2 texCoord;
};
namespace cte {
	class ObjParsing
	{
	public:
		void loadModel(const std::string& path, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);
	};
}
