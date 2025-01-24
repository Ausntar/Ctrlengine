#pragma once
#include <string>
namespace cte {
    struct RoleSettings2D {
        std::string ID;
        std::string name;
        std::string modelPath;
        std::string texturePath;
        std::string submitter;
    };
    struct Position2D {
        float x;
        float y;
    };
    struct Physics2D {
        float impactLight;
        float impactSound;

        float weight;
        float height;

        std::string type;
    };
    struct CollisionBox2D {
        float x;
        float y;
    };
}