#pragma once
#include "spdlog/spdlog.h"
#include "../Window/CteWindow.hpp"
#include "../Type/CteVulkan.hpp"
#include "../ReadJson/readJson.hpp"
#include <ft2build.h>
#include FT_FREETYPE_H
#define FONT_SIZE 24
VkImage fontTexture;
VkImageView fontTextureView;
VkDeviceMemory fontTextureMemory;
int fontTextureWidth, fontTextureHeight;
unsigned char* fontBuffer;
struct Font {
    FT_Face face;
};
Font font;
FT_Library library;
size_t size = sizeof(bufferInfo);
namespace cte {
    class Multilingual
    {
    public:
        void multilingual(std::string path);
        void setLanguage(std::string language);
        void setFont(std::string font, int size, GLFWwindow* window);
    };
}