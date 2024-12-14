#pragma once
#include "spdlog/spdlog.h"
#include "../ReadJson/readJson.hpp"
namespace cte {
    class Multilingual
    {
    public:
        void multilingual(std::string path);
        void setLanguage(std::string language);
        void setFont(std::string font);
    };
}