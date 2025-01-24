#include "CteObjModel.hpp"

#define logicalDevice device
VkDeviceSize calculateMipLevelSize(uint32_t width, uint32_t height, uint32_t nrComponents) {
    return width * height * nrComponents * sizeof(uint8_t);
}

VkDeviceSize calculateTotalImageSize(uint32_t width, uint32_t height, uint32_t nrComponents, uint32_t mipLevels) {
    VkDeviceSize totalSize = 0;
    for (uint32_t i = 1; i <= mipLevels; i++) {
        totalSize += calculateMipLevelSize(width, height, nrComponents);
        width /= 2;
        height /= 2;
        if (width <= 0) width = 1;
        if (height <= 0) height = 1;
    }
    return totalSize;
}
uint32_t findMemoryType(VkPhysicalDevice physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties) {
    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
        if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
            return i;
        }
    }

    throw std::runtime_error("failed to find suitable memory type!");
}
void endSingleTimeCommands(VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue, VkCommandBuffer commandBuffer) {
    // 结束录制命令缓冲区
    vkEndCommandBuffer(commandBuffer);

    // 提交命令缓冲区以执行
    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;

    vkQueueSubmit(graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
    vkQueueWaitIdle(graphicsQueue);

    // 销毁命令缓冲区
    vkFreeCommandBuffers(device, commandPool, 1, &commandBuffer);
}
VkCommandBuffer beginSingleTimeCommands(VkDevice device, VkCommandPool commandPool) {
    // 创建一次性命令缓冲区
    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool = commandPool;
    allocInfo.commandBufferCount = 1;

    VkCommandBuffer commandBuffer;
    vkAllocateCommandBuffers(device, &allocInfo, &commandBuffer);

    // 开始录制命令缓冲区
    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    vkBeginCommandBuffer(commandBuffer, &beginInfo);

    return commandBuffer;
}
void createBuffer(
    VkDevice logicalDevice,
    VkPhysicalDevice physicalDevice,
    VkDeviceSize size,
    VkBufferUsageFlags usage,
    VkMemoryPropertyFlags properties,
    VkBuffer& buffer,
    VkDeviceMemory& bufferMemory
) {
    // 定义VkBufferCreateInfo结构并填充所需的信息
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    // 创建VkBuffer对象
    if (vkCreateBuffer(logicalDevice, &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
        throw std::runtime_error("failed to create buffer!");
    }

    // 查询所需的内存需求
    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(logicalDevice, buffer, &memRequirements);

    // 分配内存
    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = findMemoryType(physicalDevice, memRequirements.memoryTypeBits, properties);

    if (vkAllocateMemory(logicalDevice, &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate buffer memory!");
    }

    // 将内存绑定到缓冲区
    vkBindBufferMemory(logicalDevice, buffer, bufferMemory, 0);
}
void copyBufferToImage(
    VkDevice device,
    VkCommandPool commandPool,
    VkQueue graphicsQueue,
    VkBuffer buffer,
    VkImage image,
    uint32_t width,
    uint32_t height
) {
    VkCommandBuffer commandBuffer = beginSingleTimeCommands(device, commandPool);

    VkBufferImageCopy region{};
    region.bufferOffset = 0;
    region.bufferRowLength = 0;
    region.bufferImageHeight = 0;

    region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    region.imageSubresource.mipLevel = 0;
    region.imageSubresource.baseArrayLayer = 0;
    region.imageSubresource.layerCount = 1;

    region.imageOffset = { 0, 0, 0 };
    region.imageExtent = {
        width,
        height,
        1
    };

    vkCmdCopyBufferToImage(
        commandBuffer,
        buffer,
        image,
        VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
        1,
        &region
    );

    endSingleTimeCommands(device, commandPool, graphicsQueue, commandBuffer);
}
namespace cte {
    void CteObjModel::loadObjModel(const std::string& filePath) {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
            return;
        }

        processNode(scene->mRootNode, scene);
    }

    void CteObjModel::processNode(aiNode* node, const aiScene* scene) {
        for (unsigned int i = 0; i < node->mNumMeshes; i++) {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            processMesh(mesh, scene);
        }

        for (unsigned int i = 0; i < node->mNumChildren; i++) {
            processNode(node->mChildren[i], scene);
        }
    }
    void transitionImageLayout(
        VkDevice device,
        VkCommandPool commandPool,
        VkQueue graphicsQueue,
        VkImage image,
        VkImageLayout oldLayout,
        VkImageLayout newLayout
    ) {
        VkCommandBuffer commandBuffer = beginSingleTimeCommands(device, commandPool);

        VkImageMemoryBarrier barrier{};
        barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        barrier.oldLayout = oldLayout;
        barrier.newLayout = newLayout;
        barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.image = image;
        barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        barrier.subresourceRange.baseMipLevel = 0;
        barrier.subresourceRange.levelCount = 1;
        barrier.subresourceRange.baseArrayLayer = 0;
        barrier.subresourceRange.layerCount = 1;

        VkPipelineStageFlags sourceStage;
        VkPipelineStageFlags destinationStage;

        if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) {
            barrier.srcAccessMask = 0;
            barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

            sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
            destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
        }
        else if (oldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
            barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
            barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

            sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
            destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
        }
        else {
            throw std::invalid_argument("unsupported layout transition!");
        }

        vkCmdPipelineBarrier(
            commandBuffer,
            sourceStage, destinationStage,
            0,
            0, nullptr,
            0, nullptr,
            1, &barrier
        );

        endSingleTimeCommands(device, commandPool, graphicsQueue, commandBuffer);
    }
    void CteObjModel::processMesh(aiMesh* mesh, const aiScene* scene) {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
            Vertex vertex;
            vertex.Position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
            vertex.Normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
            if (mesh->mTextureCoords[0]) {
                vertex.TexCoords = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
            }
            else {
                vertex.TexCoords = glm::vec2(0.0f, 0.0f);
            }
            vertices.push_back(vertex);
        }

        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++) {
                indices.push_back(face.mIndices[j]);
            }
        }

        // Store the mesh in a suitable data structure
        // meshes.push_back(Mesh(vertices, indices));
    }
    void createTextureImage(
        const void* data,
        uint32_t texWidth,
        uint32_t texHeight,
        uint32_t nrComponents,
        VkImage& textureImage,
        VkDeviceMemory& textureImageMemory
    ) {
        // 1. 创建VkImage
        VkImageCreateInfo imageInfo{};
        imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        imageInfo.imageType = VK_IMAGE_TYPE_2D;
        imageInfo.extent.width = texWidth;
        imageInfo.extent.height = texHeight;
        imageInfo.extent.depth = 1;
        imageInfo.mipLevels = 1;
        imageInfo.arrayLayers = 1;
        imageInfo.format = VK_FORMAT_R8G8B8A8_SRGB;
        imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
        imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        imageInfo.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
        imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
        imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        if (vkCreateImage(device, &imageInfo, nullptr, &textureImage) != VK_SUCCESS) {
            throw std::runtime_error("failed to create image!");
        }

        // 2. 为图像分配内存
        VkMemoryRequirements memRequirements;
        vkGetImageMemoryRequirements(logicalDevice, textureImage, &memRequirements);

        VkMemoryAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocInfo.allocationSize = memRequirements.size;
        allocInfo.memoryTypeIndex = findMemoryType(physicalDevice, memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

        if (vkAllocateMemory(logicalDevice, &allocInfo, nullptr, &textureImageMemory) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate image memory!");
        }

        vkBindImageMemory(logicalDevice, textureImage, textureImageMemory, 0);

        // 3. 将数据上传到图像
        uint32_t windowWidth, windowHeight;
        glfwGetWindowSize(window, reinterpret_cast<int*>(&windowWidth), reinterpret_cast<int*>(&windowHeight));
        uint32_t mipLevels = std::floor(std::log2(std::max(windowWidth, windowHeight))) + 1;
        VkDeviceSize imageSize = calculateTotalImageSize(texWidth, texHeight, nrComponents, mipLevels);

        VkBuffer stagingBuffer;
        VkDeviceMemory stagingBufferMemory;
        createBuffer(logicalDevice, physicalDevice, imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

        void* mappedData;
        vkMapMemory(logicalDevice, stagingBufferMemory, 0, imageSize, 0, &mappedData);
        memcpy(mappedData, data, static_cast<size_t>(imageSize));
        vkUnmapMemory(logicalDevice, stagingBufferMemory);

        transitionImageLayout(logicalDevice, commandPool, graphicsQueue, textureImage, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
        copyBufferToImage(logicalDevice, commandPool, graphicsQueue, stagingBuffer, textureImage, texWidth, texHeight);
        transitionImageLayout(logicalDevice, commandPool, graphicsQueue, textureImage, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

        vkDestroyBuffer(logicalDevice, stagingBuffer, nullptr);
        vkFreeMemory(logicalDevice, stagingBufferMemory, nullptr);

        // 4. 其他必要的Vulkan资源管理
        // 例如创建图像视图和采样器
    }
    void CteObjModel::loadTexture(aiMaterial* mat, aiTextureType type, std::string typeName) {
        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
            aiString str;
            mat->GetTexture(type, i, &str);
            std::string texturePath = str.C_Str();

            // Load the texture using stb_image
            int width, height, nrComponents;
            unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &nrComponents, 0);
            if (!data) {
                std::cerr << "Failed to load texture: " << texturePath << std::endl;
                continue;
            }

            // Create Vulkan texture
            VkImage textureImage;
            VkDeviceMemory textureImageMemory;
            createTextureImage(data, width, height, nrComponents, textureImage, textureImageMemory);

            // Free image data
            stbi_image_free(data);

            // Store the texture in a suitable data structure
            // textures.push_back(Texture(textureImage, textureImageMemory, typeName));
        }
    }
}